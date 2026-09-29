# 📝 BiyoKalp — Geliştirici Not Defteri

## 💡 Projeyi Zirveye Taşıyacak 3 Ekstra Öneri (Maliyetsiz / Yüksek Etkili)

Maliyeti çok düşük olan ama projenin jüri ve kabul komitesi (MIT / Harvard / ISEF) gözündeki değerini 10 katına çıkaracak 3 kritik öneri:

---

### 🧫 Öneri 1: Basit Petri Kabı Bakteri Testi (Mikrobiyolojik Kanıt)
* **Nasıl Yapılır?**
  * Eczaneden veya internetten 2 adet hazır agar besi yeri (petri kabı) temin edilir (tanesi ~50-100 ₺).
  * 1. Kaba: Arıtılmamış ham gri sudan 1 damla damlatılır.
  * 2. Kaba: Sistemdeki UV-C ışığından ve filtreden geçmiş temiz sudan 1 damla damlatılır.
  * Kaplar oda sıcaklığında (veya 37°C ılık bir ortamda) 24-48 saat bekletilir.
* **Beklenen Sonuç & Jüri Etkisi:**
  * 1. kapta sarı/beyaz bakteri kolonileri ürerken, 2. kap tertemiz kalır.
  * Bu iki kabın yan yana fotoğrafı çekilip rapora/sunuma eklendiğinde projenin arıtma başarısı tartışmasız şekilde bilimsel olarak ispatlanmış olur.

---

### 🔄 Öneri 2: Ters Yıkama (Backwash) Mekanizması
* **Nasıl Yapılır?**
  * Filtre zamanla kir ve partikülle tıkandığında sistemi söküp elle temizlemek yerine otomatik temizleme döngüsü eklenir.
  * ESP32'deki **Edge AI** algoritması sensör verilerinden *"Filtre Tıkalı / Anomali Yüksek"* uyarısı ürettiğinde, temiz su tankından ters yönde 30 saniye basınçlı su basılır.
* **Beklenen Sonuç & Jüri Etkisi:**
  * Filtre gözeneklerinde biriken tortular tahliye hattına atılır ve filtre kendi kendini temizler.
  * Sistemin bakım gereksinimi sıfıra yakın hale gelir.

---

### ⚡ Öneri 3: Yerçekimi Tabanlı Mikro Hidrotürbin (Enerji Geri Kazanımı)
* **Nasıl Yapılır?**
  * Lavabo, duş veya çatıdan aşağı doğru eğimle akan atık su borusunun içine mini bir su çarkı (3-5V mikro DC su türbini / jeneratör) yerleştirilir.
  * Su yerçekimiyle aşağı akarken pervaneyi döndürür ve elektrik üretir.
* **Beklenen Sonuç & Jüri Etkisi:**
  * Üretilen bu elektrik, sistemdeki ESP32 ve sensörlerin ihtiyacını kısmen veya tamamen karşılar.
  * Proje sadece bir arıtma sistemi olmaktan çıkıp **"Kendi Enerjisini Üreten Sıfır Karbonlu Yeşil Teknoloji"** statüsüne yükselir.

---

## 🏢 Proje Genişletmesi: Çok Katlı Apartman & Rezidans Modeli (BiyoKalp Tower)

Müstakil ev modelinden 5 katlı, 10 katlı ve 20+ katlı rezidanslara geçiş mimarisi tamamlandı:
1. **3 Kademeli Ölçeklendirme:**
   * **Kademe 1 (5 Katlı Apartman):** 10-20 Daire • Merkezi Bodrum Santrali + Daire İçi 150-750L Tampon Rezerv.
   * **Kademe 2 (10 Katlı Yapı):** 40 Daire • Çatı Yerçekimi Dağıtım Tankı (Gravity-Fed).
   * **Kademe 3 (20+ Katlı Rezidans):** 80-160 Daire • 3 Basınç Zonu + 10. Kat Ara Teknik Transfer İstasyonu.
2. **Akıllı Dolum Algoritması:** Daire rezervi 100-150L kritik seviyesine indiğinde bodrumdaki ana hidrofor otomatik devreye girer.
3. **Rejeneratif İniş Enerjisi:** Üst katlardan inen gri suyun kinetik enerjisi boru içi mikro Pelton türbinlerle elektriğe çevrilir.
4. **Yeni Web Dashboard:** `apartman.html` (Mevcut `index.html` korunarak sıfırdan bağımsız inşa edildi).

