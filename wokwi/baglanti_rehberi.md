# BiyoKalp 4-Tank Akıllı Su Geri Dönüşüm Sistemi - Wokwi Bağlantı Rehberi

Bu rehber, Wokwi simülasyon ortamında BiyoKalp sistemini kurmak için gerekli tüm donanım ve kablolama bilgilerini içerir.

## 1. Donanım Listesi
- **1x** ESP32 DevKit V1
- **1x** LCD 16x2 (I2C modülü ile)
- **1x** Aktif Buzzer
- **4x** HC-SR04 Ultrasonik Mesafe Sensörü (Tank 1, 2, 3, 4 için)
- **4x** LED (Pompaları simüle etmek için: Amber, Turuncu, Kırmızı, Camgöbeği/Mavi)
- **2x** LED (UV-C modüllerini simüle etmek için: Mavi)
- **2x** Push Buton (Manuel Karıştırma ve Mod Değiştirme)
- **2x** Potansiyometre (pH ve TDS sensörlerini simüle etmek için)
- **2x** 10KΩ Direnç (Butonlar için pull-down)
- **6x** 220Ω Direnç (LED'ler için)
- Yeteri kadar bağlantı kablosu (Jumper)

---

## 2. Pin Bağlantı Tablosu

### I2C LCD Ekran (PCF8574)
| LCD Pini | ESP32 Pini | Açıklama |
|---|---|---|
| SDA | GPIO 21 | Veri hattı |
| SCL | GPIO 22 | Saat hattı |
| VCC | 5V / 3.3V | Güç (Wokwi'de 3.3V veya 5V kullanılabilir) |
| GND | GND | Toprak |

### HC-SR04 Ultrasonik Sensörler
*Not: Wokwi'de ECHO pini için voltaj bölücü kullanmanıza gerek yoktur, doğrudan bağlanabilir.*
| Sensör | VCC | GND | TRIG Pini | ECHO Pini |
|---|---|---|---|---|
| **Tank 1** (Açık Gri) | 5V | GND | GPIO 5 | GPIO 18 |
| **Tank 2** (Koyu Gri) | 5V | GND | GPIO 19 | GPIO 23 |
| **Tank 3** (Karantina) | 5V | GND | GPIO 25 | GPIO 26 |
| **Tank 4** (Temiz Su) | 5V | GND | GPIO 27 | GPIO 14 |

### Gösterge LED'leri (Pompa ve UV-C)
*Her LED'in Anot (uzun bacak) ucuna 220Ω direnç bağlayarak ESP32'ye, Katot (kısa bacak) ucunu GND'ye bağlayın.*
| Bileşen | Renk | ESP32 Pini |
|---|---|---|
| Pompa T1 | Amber / Sarı | GPIO 2 |
| Pompa T2 | Turuncu | GPIO 4 |
| Pompa T3 | Kırmızı | GPIO 16 |
| Pompa T4 | Cyan / Mavi | GPIO 17 |
| UV-C 1 | Mavi | GPIO 15 |
| UV-C 2 | Mavi | GPIO 12 |

### Uyarı Sistemi (Buzzer)
| Buzzer Pini | ESP32 Pini / Güç |
|---|---|
| + (Artı) | GPIO 13 |
| - (Eksi) | GND |

### Kontrol Butonları (Active HIGH - 10K Pull-down)
*Butonun bir bacağı 3.3V'a, diğer bacağı ESP32 pinine ve aynı zamanda 10K direnç üzerinden GND'ye bağlanır.*
| Buton | ESP32 Pini | Açıklama |
|---|---|---|
| Mix (Karıştırma) | GPIO 34 | Manuel karıştırmayı tetikler / sayacı sıfırlar |
| Mod (Auto/Manual)| GPIO 35 | Otomatik veya manuel mod arası geçiş yapar |

### Analog Sensör Simülatörleri (Potansiyometre)
| Sensör (Pot) | VCC (Sol Bacak) | GND (Sağ Bacak) | Sinyal (Orta Bacak) | ESP32 Pini |
|---|---|---|---|---|
| pH Sensörü | 3.3V | GND | Orta | GPIO 32 |
| TDS Sensörü | 3.3V | GND | Orta | GPIO 33 |

---

## 3. Renk Kodlu Kablo Önerileri (Karmaşıklığı Önlemek İçin)
- **Kırmızı:** 5V Güç hatları
- **Turuncu:** 3.3V Güç hatları
- **Siyah:** GND (Toprak) hatları
- **Yeşil / Sarı:** I2C hatları (SDA, SCL)
- **Mavi / Beyaz:** Ultrasonik TRIG ve ECHO
- **Mor:** Buton ve Analog sinyal hatları

---

## 4. Adım Adım Kurulum Sırası
1. **Güç Dağıtımı:** Breadboard üzerindeki güç yollarına ESP32'den 3.3V, 5V (VIN) ve GND bağlantılarını çekin.
2. **I2C LCD:** LCD modülünü breadboard'a yerleştirip I2C, güç ve toprak kablolarını takın.
3. **HC-SR04 Sensörleri:** 4 sensörü yerleştirin, TRIG ve ECHO pinlerini tabloya göre bağlayın.
4. **Butonlar ve Potansiyometreler:** Analog giriş (GPIO 34, 35 sadece giriştir) olduğu için pull-down dirençlerine dikkat ederek butonları kurun. Potansiyometreleri bağlayın.
5. **LED'ler ve Buzzer:** Çıkış birimlerini uygun dirençlerle bağlayarak devreyi tamamlayın.

---

## 5. Wokwi'de Sık Yapılan Hatalar ve Dikkat Edilmesi Gerekenler
- **Kütüphane Eksikliği:** LCD'nin çalışması için projede `libraries.txt` sekmesi açıp içine `LiquidCrystal I2C` yazmanız **şarttır**.
- **Sensör Ayarları:** Wokwi simülasyonunda sensörün üzerine tıkladığınızda mesafe sürgüsü çıkar. Mesafeyi 160cm (Boş) ile 40cm (Dolu/1500L) arasında değiştirerek sistemi test edebilirsiniz.
- **GPIO 34/35 Kısıtlaması:** ESP32'de 34, 35, 36, 39 numaralı pinler **sadece giriş (INPUT)** olarak kullanılabilir. Bu pinlere pull-up direnci bağlanamaz. Bu yüzden projedeki butonlara fiziksel 10K pull-down direnci eklemeyi (simülasyonda) unutmayın.
- **Güç Tüketimi:** Simülasyonda sorun olmasa da gerçekte 4 ultrasonik sensör 5V ile beslenmelidir. Wokwi'de ESP32'nin 3.3V pinini (ECHO 3.3V toleransı için) veya 5V(VIN) pinini kullanabilirsiniz.

---

## 6. Wokwi İçin Kütüphane Ayarı
`libraries.txt` isimli bir dosya oluşturun ve içine sadece şu metni ekleyin:
```text
LiquidCrystal I2C
```

## 7. Sorun Giderme
- **Ekranda Yazı Çıkmıyor:** I2C pinlerinin SDA=21, SCL=22 olduğuna ve I2C adresinin `0x27` (kodda belirtildiği gibi) olduğuna emin olun.
- **Sürekli Kırmızı LED / Alarm:** Potansiyometre değerlerini kontrol edin. pH değeri <5.5 veya >9.0, ya da TDS >800 ise karantina tankı (T3) uyarı verir.
- **Butonlar Çalışmıyor:** Pull-down dirençlerinin doğru şekilde (buton çıkışından GND'ye) bağlandığından emin olun.
