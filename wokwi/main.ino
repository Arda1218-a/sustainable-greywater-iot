#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// --- PIN TANIMLAMALARI ---
// LCD I2C
#define I2C_SDA 21
#define I2C_SCL 22

// HC-SR04 Sensörleri (Trig, Echo)
#define T1_TRIG 5
#define T1_ECHO 18
#define T2_TRIG 19
#define T2_ECHO 23
#define T3_TRIG 25
#define T3_ECHO 26
#define T4_TRIG 27
#define T4_ECHO 14

// Buzzer
#define BUZZER_PIN 13

// LED'ler (Pompalar ve UV-C)
#define PUMP_T1_LED 2
#define PUMP_T2_LED 4
#define PUMP_T3_LED 16
#define PUMP_T4_LED 17
#define UVC_1_LED 15
#define UVC_2_LED 12

// Butonlar
#define MIX_BUTTON 34
#define MODE_BUTTON 35

// Analog Sensörler (Potansiyometreler)
#define PH_PIN 32
#define TDS_PIN 33

// --- SABITLER ---
const int TANK_HEIGHT = 160; // cm
const float TANK_VOLUME = 2000.0; // Litre
const unsigned long MIX_INTERVAL = 7200; // 2 saat (saniye cinsinden)
const unsigned long MIX_DURATION = 900;  // 15 dakika (saniye cinsinden)
const unsigned long WARNING_TIME = 900;  // 15 dakika kala uyarı (saniye)

// --- DEGISKENLER ---
LiquidCrystal_I2C lcd(0x27, 16, 2);

float t1_dist, t2_dist, t3_dist, t4_dist;
float t1_pct, t2_pct, t3_pct, t4_pct;
float t1_vol, t2_vol, t3_vol, t4_vol;

float phValue = 7.0;
int tdsValue = 300;
String t3_risk = "DUSUK";

// --- EDGE AI / TinyML DEGISKENLERI ---
float filterHealthIndex = 100.0; // %100 -> %0
float anomalyScore = 0.0;        // 0.0 (Normal) - 1.0 (Kritik Anomali)
int estimatedDaysRemaining = 90; // Kalan tahmini filtre omru (gun)
String aiStatus = "SAGLIKLI";
unsigned long totalFilteredVolume = 0; // Toplam aritilan su hacmi

bool autoMode = true;
bool mixingActive = false;
unsigned long mixTimer = MIX_INTERVAL;
unsigned long mixDurationTimer = 0;
bool warningGiven = false;

int screenState = 0;
unsigned long lastScreenUpdate = 0;
unsigned long lastSerialUpdate = 0;
unsigned long lastSensorRead = 0;
unsigned long lastSecondTick = 0;
unsigned long buzzerLastBlink = 0;

bool buzzerActive = false;
bool isCritical = false;
bool t3HighRisk = false;

// --- FONKSIYON BİLDİRİMLERİ ---
float readUltrasonic(int trigPin, int echoPin);
void readSensors();
void updateTankLEDs();
void handleMixingLogic();
void handleLCD();
void printSerial();
void warnBuzzer();
void mixStartBuzzer();
void criticalBuzzer();
void quarantineBuzzer();
void formatTime(unsigned long timeInSeconds, char* buffer);
String getStatus(float pct);

void setup() {
  Serial.begin(115200);
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();
  
  // Pin Modları
  pinMode(T1_TRIG, OUTPUT); pinMode(T1_ECHO, INPUT);
  pinMode(T2_TRIG, OUTPUT); pinMode(T2_ECHO, INPUT);
  pinMode(T3_TRIG, OUTPUT); pinMode(T3_ECHO, INPUT);
  pinMode(T4_TRIG, OUTPUT); pinMode(T4_ECHO, INPUT);
  
  pinMode(BUZZER_PIN, OUTPUT);
  
  pinMode(PUMP_T1_LED, OUTPUT);
  pinMode(PUMP_T2_LED, OUTPUT);
  pinMode(PUMP_T3_LED, OUTPUT);
  pinMode(PUMP_T4_LED, OUTPUT);
  pinMode(UVC_1_LED, OUTPUT);
  pinMode(UVC_2_LED, OUTPUT);
  
  pinMode(MIX_BUTTON, INPUT);
  pinMode(MODE_BUTTON, INPUT);
  
  // Başlangıç animasyonu
  lcd.setCursor(0, 0);
  lcd.print("BiyoKalp v1.0");
  lcd.setCursor(0, 1);
  lcd.print("Baslatiliyor...");
  delay(2000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();
  
  // 1 Saniyelik Zamanlayıcı (Tick)
  if (currentMillis - lastSecondTick >= 1000) {
    lastSecondTick = currentMillis;
    if (!mixingActive) {
      if (mixTimer > 0) mixTimer--;
    } else {
      if (mixDurationTimer > 0) mixDurationTimer--;
      else {
        mixingActive = false;
        mixTimer = MIX_INTERVAL;
        digitalWrite(PUMP_T1_LED, LOW);
        digitalWrite(PUMP_T2_LED, LOW);
        digitalWrite(PUMP_T3_LED, LOW);
        digitalWrite(PUMP_T4_LED, LOW);
      }
    }
  }

  // Sensör Okuma
  if (currentMillis - lastSensorRead >= 500) {
    lastSensorRead = currentMillis;
    readSensors();
    updateTankLEDs();
  }

  // Buton Kontrolü
  static bool lastModeBtn = LOW;
  bool currentModeBtn = digitalRead(MODE_BUTTON);
  if (currentModeBtn == HIGH && lastModeBtn == LOW) {
    autoMode = !autoMode;
    Serial.println(autoMode ? "Mod: AUTO" : "Mod: MANUAL");
    delay(50); // Debounce
  }
  lastModeBtn = currentModeBtn;

  static bool lastMixBtn = LOW;
  bool currentMixBtn = digitalRead(MIX_BUTTON);
  if (currentMixBtn == HIGH && lastMixBtn == LOW) {
    if (autoMode) {
      mixTimer = MIX_INTERVAL; // Reset timer
      mixingActive = false;
      warningGiven = false;
      Serial.println("Karistirma timer sifarlandi (AUTO).");
    } else {
      if (!mixingActive) {
        mixingActive = true;
        mixDurationTimer = MIX_DURATION;
        mixStartBuzzer();
        Serial.println("Manuel karistirma baslatildi.");
      }
    }
    delay(50); // Debounce
  }
  lastMixBtn = currentMixBtn;

  handleMixingLogic();

  // LCD Ekran Güncelleme (4 saniyede bir)
  if (currentMillis - lastScreenUpdate >= 4000) {
    lastScreenUpdate = currentMillis;
    screenState = (screenState + 1) % 5;
    lcd.clear();
  }
  handleLCD();

  // Seri Port Çıktısı (5 saniyede bir)
  if (currentMillis - lastSerialUpdate >= 5000) {
    lastSerialUpdate = currentMillis;
    printSerial();
  }
  
  // Kritik Durum Buzzer Yönetimi
  if (isCritical) {
    if (currentMillis - buzzerLastBlink >= 100) {
      buzzerLastBlink = currentMillis;
      buzzerActive = !buzzerActive;
      digitalWrite(BUZZER_PIN, buzzerActive ? HIGH : LOW);
    }
  } else if (t3HighRisk && !mixingActive) {
    // Quarantine buzzer logic is handled once on state change or periodically
  } else {
    digitalWrite(BUZZER_PIN, LOW); // Default off if not critical
  }
}

float readUltrasonic(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH, 30000); // 30ms timeout
  if (duration == 0) return TANK_HEIGHT; // Eğer okuma yoksa boş say (mesafe = boy)
  return duration * 0.034 / 2;
}

void readSensors() {
  t1_dist = readUltrasonic(T1_TRIG, T1_ECHO);
  t2_dist = readUltrasonic(T2_TRIG, T2_ECHO);
  t3_dist = readUltrasonic(T3_TRIG, T3_ECHO);
  t4_dist = readUltrasonic(T4_TRIG, T4_ECHO);

  auto calcTank = [](float dist, float &pct, float &vol) {
    if (dist > TANK_HEIGHT) dist = TANK_HEIGHT;
    float waterHeight = TANK_HEIGHT - dist;
    if (waterHeight < 0) waterHeight = 0;
    pct = (waterHeight / TANK_HEIGHT) * 100.0;
    vol = (pct / 100.0) * TANK_VOLUME;
  };

  calcTank(t1_dist, t1_pct, t1_vol);
  calcTank(t2_dist, t2_pct, t2_vol);
  calcTank(t3_dist, t3_pct, t3_vol);
  calcTank(t4_dist, t4_pct, t4_vol);

  // Potansiyometre okumaları
  int phRaw = analogRead(PH_PIN);
  phValue = map(phRaw, 0, 4095, 0, 1400) / 100.0; // 0.0 - 14.0
  
  int tdsRaw = analogRead(TDS_PIN);
  tdsValue = map(tdsRaw, 0, 4095, 0, 1000); // 0 - 1000 PPM

  // Risk analizi (T3)
  t3HighRisk = false;
  if (phValue < 5.5 || phValue > 9.0 || tdsValue > 800) {
    t3_risk = "YUKSEK RISK";
    t3HighRisk = true;
  } else if (tdsValue > 500) {
    t3_risk = "ORTA RISK";
  } else {
    t3_risk = "DUSUK RISK";
  }
  
  // Kritik Seviye kontrolü (<%20)
  isCritical = (t1_pct < 20.0 || t2_pct < 20.0 || t3_pct < 20.0 || t4_pct < 20.0);

  // Edge AI Çıkarım Fonksiyonu
  runEdgeAIInference();
}

void runEdgeAIInference() {
  // 1. Anomali Skoru Hesabı (pH ve TDS sapması + Doygunluk Matrisi)
  float phDeviation = abs(phValue - 7.2) / 7.2; // İdeal 7.2'den sapma
  float tdsStress = (float)tdsValue / 1000.0;    // TDS yük faktörü
  
  // Nöral benzeri ağırlıklı anomali skoru (0.0 - 1.0)
  anomalyScore = (phDeviation * 0.4) + (tdsStress * 0.6);
  if (anomalyScore > 1.0) anomalyScore = 1.0;

  // 2. Filtre Sağlık İndeksi & Kalan Ömür Kestirimi
  // Her yüksek stresli döngüde filtre ömrü yıpranır
  float degradationRate = (anomalyScore * 0.05) + 0.005;
  if (filterHealthIndex > degradationRate) {
    filterHealthIndex -= degradationRate;
  } else {
    filterHealthIndex = 0.0;
  }

  // Kalan gün tahmini
  estimatedDaysRemaining = (int)((filterHealthIndex / 100.0) * 90.0);

  // 3. AI Durum Sınıflandırması
  if (anomalyScore > 0.75 || filterHealthIndex < 15.0) {
    aiStatus = "KRITIK/TIKALI";
  } else if (anomalyScore > 0.45 || filterHealthIndex < 40.0) {
    aiStatus = "BAKIM YAKIN";
  } else {
    aiStatus = "OPTIMAL";
  }
}

void updateTankLEDs() {
  if (mixingActive) {
    // Karıştırma sırasında pompalar hızlı yanıp söner
    bool blinkState = (millis() / 200) % 2;
    digitalWrite(PUMP_T1_LED, blinkState);
    digitalWrite(PUMP_T2_LED, blinkState);
    digitalWrite(PUMP_T3_LED, blinkState);
    digitalWrite(PUMP_T4_LED, blinkState);
    digitalWrite(UVC_1_LED, HIGH);
    digitalWrite(UVC_2_LED, HIGH);
    return;
  }

  digitalWrite(UVC_1_LED, LOW);
  digitalWrite(UVC_2_LED, LOW);

  auto setLedState = [](float pct, int pin, bool isT3) {
    if (pct < 20.0) {
      digitalWrite(pin, (millis() / 200) % 2); // Hızlı blink
    } else if (pct < 40.0) {
      digitalWrite(pin, (millis() / 1000) % 2); // Yavaş blink
    } else {
      digitalWrite(pin, HIGH); // Sabit
    }
  };

  setLedState(t1_pct, PUMP_T1_LED, false);
  setLedState(t2_pct, PUMP_T2_LED, false);
  
  if (t3HighRisk) {
    digitalWrite(PUMP_T3_LED, (millis() / 100) % 2); // Çok hızlı blink
  } else {
    setLedState(t3_pct, PUMP_T3_LED, true);
  }
  
  setLedState(t4_pct, PUMP_T4_LED, false);
}

void handleMixingLogic() {
  if (autoMode) {
    if (mixTimer == WARNING_TIME && !warningGiven) {
      warnBuzzer();
      warningGiven = true;
    }
    
    if (mixTimer == 0 && !mixingActive) {
      mixingActive = true;
      mixDurationTimer = MIX_DURATION;
      mixStartBuzzer();
    }
    
    if (mixingActive && mixDurationTimer == 0) {
      mixingActive = false;
      mixTimer = MIX_INTERVAL;
      warningGiven = false;
    }
  }
}

void handleLCD() {
  switch (screenState) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("BiyoKalp v1.0   ");
      lcd.setCursor(0, 1);
      lcd.print("Sistem: AKTIF   ");
      break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("T1:"); lcd.print((int)t1_pct); lcd.print("% T2:"); lcd.print((int)t2_pct); lcd.print("%  ");
      lcd.setCursor(0, 1);
      lcd.print("T3:"); lcd.print((int)t3_pct); lcd.print("% T4:"); lcd.print((int)t4_pct); lcd.print("%  ");
      break;
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("pH:"); lcd.print(phValue, 1); lcd.print(" TDS:"); lcd.print(tdsValue); lcd.print("  ");
      lcd.setCursor(0, 1);
      if (t3HighRisk) {
        lcd.print("T3:YUKSEK RISK  ");
      } else {
        lcd.print("Temp: -- Turb:OK");
      }
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("Karistirma: ");
      lcd.print(autoMode ? "AUTO  " : "MANUAL");
      lcd.setCursor(0, 1);
      if (mixingActive) {
        char buf[9];
        formatTime(mixDurationTimer, buf);
        lcd.print(buf); lcd.print(" aktif");
      } else {
        char buf[9];
        formatTime(mixTimer, buf);
        lcd.print(buf); lcd.print(" kaldi ");
      }
      break;
    case 4:
      lcd.setCursor(0, 0);
      lcd.print("AI Saglik:%");
      lcd.print((int)filterHealthIndex);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print("Omur:");
      lcd.print(estimatedDaysRemaining);
      lcd.print("g [");
      lcd.print(aiStatus.substring(0, 4));
      lcd.print("]");
      break;
  }
}

String getStatus(float pct) {
  if (pct < 20.0) return "KRITIK";
  if (pct < 40.0) return "DUSUK";
  if (pct > 80.0) return "DOLU";
  return "NORMAL";
}

void printSerial() {
  Serial.println("=== BiyoKalp Status ===");
  Serial.printf("T1: %.0fL (%.1f%%) | %s\n", t1_vol, t1_pct, getStatus(t1_pct).c_str());
  Serial.printf("T2: %.0fL (%.1f%%) | %s\n", t2_vol, t2_pct, getStatus(t2_pct).c_str());
  Serial.printf("T3: %.0fL (%.1f%%) | %s [Risk: %s]\n", t3_vol, t3_pct, getStatus(t3_pct).c_str(), t3_risk.c_str());
  Serial.printf("T4: %.0fL (%.1f%%) | %s\n", t4_vol, t4_pct, getStatus(t4_pct).c_str());
  Serial.printf("pH: %.2f | TDS: %d PPM\n", phValue, tdsValue);
  Serial.printf("Edge AI: Filtre Saglik: %%%.1f | Anomali: %.2f | Kalan: %d Gun | Durum: %s\n", 
                filterHealthIndex, anomalyScore, estimatedDaysRemaining, aiStatus.c_str());
  
  char buf[9];
  formatTime(mixingActive ? mixDurationTimer : mixTimer, buf);
  Serial.printf("Karistirma: %s %s | Mod: %s\n", buf, mixingActive ? "aktif" : "kaldi", autoMode ? "AUTO" : "MANUAL");
  Serial.println("======================");
}

void formatTime(unsigned long timeInSeconds, char* buffer) {
  int h = timeInSeconds / 3600;
  int m = (timeInSeconds % 3600) / 60;
  int s = timeInSeconds % 60;
  sprintf(buffer, "%02d:%02d:%02d", h, m, s);
}

void warnBuzzer() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
}

void mixStartBuzzer() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(1000);
  digitalWrite(BUZZER_PIN, LOW);
}

void quarantineBuzzer() {
  for (int i=0; i<2; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(600);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
  }
  digitalWrite(BUZZER_PIN, HIGH);
  delay(200);
  digitalWrite(BUZZER_PIN, LOW);
}
