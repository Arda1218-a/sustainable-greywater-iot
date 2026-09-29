# 🏢 BiyoKalp Tower — Çok Katlı Yapılar ve Rezidanslar İçin Biyomimetik Su Mimarisi

**Proje Genişletmesi:** 3 Kademeli Çok Katlı Bina Su Dağıtım ve Geri Kazanım Ağı  
**Ölçek:** 5 Katlı Apartmanlar $\rightarrow$ 5-10 Katlı Orta Ölçekli Binalar $\rightarrow$ 20+ Katlı Gökdelenler & Rezidanslar  

---

## 🏗️ 1. MÜHENDİSLİK ANALİZİ & 3 KADEMELİ MİMARİ

Müstakil evden çok katlı binalara geçildiğinde karşılaşılan en büyük 2 fiziksel engel:
1. **Hidrostatik Basınç & Pompalama Enerjisi:** 20 katlı bir binada (yaklaşık 60 metre yükseklik) en alt kattaki boru basıncı $\approx 6 \text{ bar}$ olur. Aşağıdan yukarıya her musluk açıldığında su basmaya çalışmak devasa pompalar gerektirir ve elektrik tüketimini uçurur.
2. **Statik Yük & Daire İçi Alan:** Daire içine 1 tonluk (1000 kg) tank koymak hem $\approx 1.2 \text{ m}^2$ yaşam alanı çalar hem de döşeme betonuna noktasal statik yük bindirir.

---

## ⚡ 2. HİDROLİK ÇÖZÜM TERCİHİ: "AORTA & KILCAL DAMAR HİBRİT MİMARİSİ"

Kalp kanı nasıl bütün vücuda (beyinden ayak parmaklarına kadar) dengeli dağıtıyorsa, bina içinde de bu mantık uygulanır:

```
                          [ÇATI YERÇEKİMİ TANKI]
                                    │
    ┌───────────────────────────────┴───────────────────────────────┐
    │  20+ KAT (ZON 3: ÜST ZON - 15-20+ Katlar)                     │
    │  Daireler (Daire Başı 150-250L Kompakt Rezerv / Asma Tavan)   │
    ├───────────────────────────────────────────────────────────────┤
    │  10-15 KAT (ZON 2: ORTA ZON - 8-14 Katlar)                    │
    │  [10. Kat Ara Teknik Transfer & Basınç Kırıcı Buffer]         │
    ├───────────────────────────────────────────────────────────────┤
    │  1-5 KAT (ZON 1: ALT ZON - 1-7 Katlar)                        │
    │  Basınç Düşürücü Regülatörler (PRV)                           │
    └───────────────────────────────┬───────────────────────────────┘
                                    │
                       ▲ [ANA AORT YÜKSELTİCİ HATTI]
                       │ (Gece/Boşta Yavaş Dolum)
                                    │
             [BODRUM KAT: BİYOKALP MERKEZİ ARITMA SANTRALİ]
             (T1 Gri Su, T2 Koyu Gri, T3 Karantina, T4 Temiz Rezerv)
```

---

## 📊 3. KADEME KARŞILAŞTIRMA TABLOSU

| Kademe | Bina Tipi | Kat / Daire Sayısı | Dağıtım & Pompalama Stratejisi | Tank Konfigürasyonu |
|---|---|---|---|---|
| **Kademe 1** | 5 Katlı Apartman | 5 Kat, 10-20 Daire (2-4 daire/kat) | **Merkezi Bodrum Arıtma + Akıllı Hidrofor + Daire Başı 150L Asma Tavan Tamponu** | Bodrum: 4x 3000L<br>Daireler: 150L Kompakt |
| **Kademe 2** | 5-10 Katlı Orta Yapılar | 10 Kat, 20-40 Daire | **Bodrum Arıtma + Çatı Yerçekimi Dağıtım Tankı (Gravity-Fed)** | Bodrum: 4x 6000L<br>Çatı: 3000L Yerçekimi |
| **Kademe 3** | 20+ Katlı Rezidans / Gökdelen | 20+ Kat, 80-160+ Daire | **3-Kademeli Basınç Zonlama (Pressure Zoning) + 10. Kat Ara Transfer İstasyonu + İniş Hattı Enerji Geri Kazanımı (Mikro Türbin)** | Bodrum: 4x 15.000L<br>10. Kat: 4.000L<br>Çatı: 6.000L |

---

## 💡 4. DÖNGÜSEL İNOVASYON: İNİŞ HATTINDA ELEKTRİK ÜRETİMİ (REJENERATİF SU ENERJİSİ)

20. kattan bodruma inen gri su (duş ve lavabo atıkları) muazzam bir yerçekimi kinetik enerjisine sahiptir:
* İniş ana kolon borusuna her 5 katta bir **Helisel Pelton Tipi Mini Hidro-Türbin** yerleştirilir.
* Su aşağı inerken türbinleri döndürür ve elektrik üretir.
* Bu elektrik, bodrumdaki temiz suyu yukarı basan pompaların elektrik ihtiyacının **%35-45'ini doğrudan karşılar!**

---

## 📱 5. DAİRE SAKİNLERİ VE BİNA YÖNETİMİ İÇİN AKILLI ÖZELLİKLER

1. **Daire Bazlı Su Tasarruf Paylaşımı & Fatura İndirimi:**
   * Her dairenin gri su katkısı ve arıtılmış su tüketimi anlık ölçülür.
   * Apartman aidatından arıtılan su kadar otomatik indirim yapılır.
2. **Akıllı Gece Dolum Algoritması (Peak-Shaving):**
   * Pompalar gündüz saatlerinde elektrik pahalıyken ve su kullanımı yoğunken sürekli çalışmaz.
   * Gece 02:00 - 05:00 saatleri arasında (elektriğin en ucuz olduğu tarife) çatı ve ara tampon tanklar sessizce doldurulur.
3. **Daire İçi Kaçak İzolasyon Vanası:**
   * Her dairenin girişindeki motorlu vana, dairede kaçak veya anormal akış algılandığında sistemi 1 saniyede keser.
