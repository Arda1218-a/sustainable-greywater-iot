# 💧 BiyoKalp & BiyoKalp Tower
> **Biyomimetik Akıllı Su Geri Kazanım, Çok Katlı Hidrostatik Dağıtım & Edge/NVIDIA AI Ekosistemi**  
> *Biomimetic Greywater Recycling, Multi-Tier Hydrostatic Distribution & Edge/NVIDIA AI Ecosystem*

[![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT)
[![Hardware: ESP32](https://img.shields.io/badge/Hardware-ESP32-red.svg)](https://espressif.com)
[![Wokwi Simulator](https://img.shields.io/badge/Wokwi-Live%20Simulation-brightgreen.svg)](https://wokwi.com)
[![NVIDIA NIM](https://img.shields.io/badge/NVIDIA%20NIM-Llama%203.3%2070B-76b900.svg)](https://build.nvidia.com)
[![Target: MIT & ISEF](https://img.shields.io/badge/Competition-MIT%20%26%20ISEF%20Ready-purple.svg)]()

> 🌐 **CANLI SİTE BAĞLANTILARI (LIVE DEMOS):**  
> 🏢 **[BiyoKalp Tower (Apartman & Rezidans Modeli)](https://arda1218-a.github.io/sustainable-greywater-iot/apartman.html)** • 🏡 **[Müstakil Ev Modeli](https://arda1218-a.github.io/sustainable-greywater-iot/)** • 📽️ **[Akademik Jüri Sunumu](https://arda1218-a.github.io/sustainable-greywater-iot/sunum/index.html)**

---

## 🌟 Projeye Genel Bakış (Project Overview)

BiyoKalp, insan kardiyovasküler dolaşım sisteminden (sağ/sol atriyum, ventriküller, tek yönlü biyolojik kapakçıklar ve pulsatil akış) ilham alan; hem **müstakil evler** hem de **5 ila 20+ katlı rezidanslar** için geliştirilmiş yeni nesil akıllı gri su geri kazanım ve enerji hasadı altyapısıdır.

```
                  ┌───────────────────────────────┐
                  │      BİYOKALP EKOSİSTEMİ      │
                  └──────────────┬────────────────┘
                                 │
         ┌───────────────────────┴───────────────────────┐
         ▼                                               ▼
  🏡 MÜSTAKİL EV MODELİ                           🏢 BİYOKALP TOWER
  • 4 Ayrık Tank (T1, T2, T3, T4)                 • 5 - 10 - 20+ Katlı Ölçeklendirme
  • ESP32 + Wokwi Devre Simülasyonu               • 3-Kademeli Basınç Zonlama (PRV)
  • C++ Edge AI Anomali Kestirimi                 • 10. Kat Ara Teknik Transfer İstasyonu
  • Otomatik Periyodik Karıştırma                 • İniş Hattı Pelton Türbin Enerji Hasadı
  • Web Dashboard (`index.html`)                  • NVIDIA Llama 3.3 70B AI (`apartman.html`)
```

---

## 🖥️ Canlı Web Dashboard'ları & Sunum (Web Dashboards)

| Arayüz | Canlı Bağlantı (Live URL) | Kaynak Dosya | Açıklama |
|---|---|---|---|
| 🏢 **Apartman & Rezidans Dashboard'u** | [**Canlı Aç (apartman.html)**](https://arda1218-a.github.io/sustainable-greywater-iot/apartman.html) | [`apartman.html`](apartman.html) | 5, 10 ve 20+ katlı bina hidrolik kesiti, daire tampon rezervi ve **NVIDIA Llama 3.3 AI**. |
| 🏡 **Müstakil Ev Dashboard'u** | [**Canlı Aç (index.html)**](https://arda1218-a.github.io/sustainable-greywater-iot/) | [`index.html`](index.html) | 4 tankın canlı su seviyeleri, sensörler (pH, TDS, Bulanıklık) ve karıştırma sayaçları. |
| 📽️ **Akademik Jüri Sunumu** | [**Canlı Aç (sunum)**](https://arda1218-a.github.io/sustainable-greywater-iot/sunum/index.html) | [`sunum/index.html`](sunum/index.html) | 15 slaytlık, klavye yön tuşlarıyla kontrol edilen interaktif akademik sunum. |

---

## ⚡ Wokwi Canlı Donanım Simülasyonu (Wokwi Simulation)

Fiziksel donanıma gerek kalmadan tüm devreyi tarayıcıda çalıştırmak için:
1. **[wokwi.com](https://wokwi.com)** adresinde yeni bir **ESP32** projesi açın.
2. `sketch.ino` içine [`wokwi/main.ino`](wokwi/main.ino) kodunu yapıştırın.
3. `diagram.json` sekmesine [`wokwi/diagram.json`](wokwi/diagram.json) dosyasını yapıştırın (tüm 25 bileşen ve kablolar otomatik bağlanır).
4. `libraries.txt` sekmesine `LiquidCrystal I2C` yazıp simülasyonu başlatın!

Detaylı bağlantı ve pin haritası için: 👉 [`wokwi/baglanti_rehberi.md`](wokwi/baglanti_rehberi.md)

---

## 🧠 Yapay Zeka Mimarisi (AI & Edge Analytics)

1. **Uçta Yapay Zeka (Edge AI - TinyML / ESP32):**
   * ESP32 üzerinde çalışan C++ algoritması, pH ve TDS sapmalarından bir *Anomali Skoru (0.0 - 1.0)* türetir.
   * Filtre aşınma hızını ve kalan ömrü gün cinsinden tahmin eder (`estimatedDaysRemaining`).
   * LCD ekranında 5. sayfa olarak durum gösterilir.

2. **Bulut Teşhis Motoru (NVIDIA NIM Llama 3.3 70B):**
   * `apartman.html` üzerinde binanın anlık hidrostatik basıncını, pompa çağrılarını ve bodrum santralini canlı telemetri olarak toplar.
   * NVIDIA'nın `meta/llama-3.3-70b-instruct` modeli üzerinden yöneticilere ve mühendislere anlık doğal dille Türkçe arıza/tasarruf raporu üretir.

---

## 🏗️ Dizin Yapısı (Repository Structure)

```
su/
├── index.html                   # Müstakil ev dashboard'u
├── style.css                    # Müstakil ev stilleri
├── app.js                       # Müstakil ev JS simülasyon motoru
├── apartman.html                # Çok katlı bina & rezidans dashboard'u
├── apartman.css                 # Rezidans bina stilleri
├── apartman.js                  # Rezidans hidrolik ve NVIDIA AI motoru
├── config.example.js            # NVIDIA API anahtarı şablonu
├── not_defteri.md               # Geliştirici notları ve altın öneriler
├── maliyet_ve_bakim_takvimi.md  # TTO teknik şartnamesi, 5 katmanlı filtreleme & savunma rehberi
├── README.md                    # Proje ana tanıtım belgesi
├── wokwi/                       # ESP32 simülasyon dosyaları
│   ├── main.ino                 # C++ Arduino/ESP32 kaynak kodu
│   ├── diagram.json             # Wokwi otomatik devre bağlantı şeması
│   ├── libraries.txt            # Kütüphane bağımlılığı (LiquidCrystal I2C)
│   └── baglanti_rehberi.md      # Pin-pin detaylı montaj rehberi
├── rapor/                       # Akademik ve mimari teknik raporlar
│   ├── BiyoKalp_Akademik_Rapor.md
│   └── BiyoKalp_Apartman_Rezidans_Mimari.md
└── sunum/                       # İnteraktif slayt sunumu
    ├── index.html               # 15 Slaytlık web sunumu
    └── sunum.md                 # Konuşmacı notları ve jüri savunma kılavuzu
```

---

## 🚀 Yerel Kurulum & Çalıştırma (Quick Start)

```bash
# 1. Repoyu klonlayın
git clone https://github.com/KULLANICI_ADINIZ/BiyoKalp.git
cd BiyoKalp

# 2. NVIDIA AI özelliğini aktifleştirmek için (Opsiyonel)
cp config.example.js config.js
# config.js dosyasını açıp build.nvidia.com'dan aldığınız API key'i yazın

# 3. Web Arayüzlerini Açın
# apartman.html veya index.html dosyasını herhangi bir modern tarayıcıda açın
```

---

## ⚖️ Fikri Mülkiyet, Bağımsızlık & Hak Sahipliği Beyanı (Intellectual Property Statement)

> ### 📌 ÖNEMLİ HUKUKİ VE AKADEMİK BİLDİRİM:
> **Bu projenin (BiyoKalp ve BiyoKalp Tower) tüm fikri mülkiyet, tasarım, mimari ve telif hakları tamamen ve münhasıran ARDA'ya aittir.**
> 
> * **Kurumsal Bağımsızlık:** Bu çalışma, yazarın kayıtlı olduğu, kazandığı veya ileride eğitim alacağı **hiçbir üniversitenin, enstitünün, araştırma merkezinin veya üçüncü taraf akademik kurumun dahiliyeti, finansmanı, akademik danışmanlığı, gözetimi veya laboratuvar katkısı OLMADAN**, %100 bağımsız kişisel bir AR-GE girişimi olarak ortaya konmuştur.
> * **Hak İddiası Kısıtlaması:** Hiçbir üniversite veya eğitim kurumu bu projenin algoritmaları, donanım şemaları, hidrolik mimarisi veya patent potansiyeli üzerinde kurumsal hak veya ortaklık iddia edemez.
> 
> ---
> 
> ### 🤝 Geliştirici Rolleri & İnsan-Yapay Zeka Ortak Mühendisliği (Human-AI Co-Engineering)
> Bu proje, modern çağın öncül **İnsan + Yapay Zeka (Centaur Engineering)** felsefesiyle hayata geçirilmiştir:
> 
> * **👤 Baş Mimar & Proje Sahibi (Lead Inventor & Chief Architect) — Arda:**
>   * Kalp sirkülasyonundan esinlenen kardiyovasküler biyomimetik konseptin fikir babası.
>   * 4-Tanklı ayrık gri su yönetimi, karantina tankı prensibi ve daire tampon rezervi mimarisinin kurgulanması.
>   * Çok katlı yapılarda basınç zonlama, hidrostatik dengeleme ve tüm sistem gereksinimlerinin belirlenmesi.
> * **🤖 Yapay Zeka Mühendislik Ortağı (AI Co-Engineer & Technical Multiplier) — Antigravity AI:**
>   * Donanım bağlantı matrisinin (`diagram.json`) ve C++ Edge AI algoritmalarının kodlanması.
>   * Asenkron web dashboard'ları, telemetri motoru ve NVIDIA NIM Llama 3.3 entegrasyonu desteği.
>   * Hidrolik matematik modellerin ve akademik rapor belgelerinin derlenmesi.

---

## 📜 Lisans
Bu proje [MIT Lisansı](LICENSE) kapsamında açık kaynak olarak geliştirilmiştir. Kodlar ve mimari referans gösterilmek kaydıyla incelenebilir.
