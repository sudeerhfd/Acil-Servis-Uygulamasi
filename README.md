
# Acil-Servis-Uygulmasi


Bu proje, acil servis yönetim sistemi için bir komut satırı uygulamasıdır. Bu uygulama, hastaların bilgilerini yönetmek, reçete numaraları üretmek, hasta bilgilerini görüntülemek, hastaları listelemek ve hastaları silmek için kullanılır.

## Özellikler

- Hasta ekleme
- Reçete numarası üretme
- Hasta bilgilerini görüntüleme
- Hastaları listeleme
- Hasta silme

## Kurulum

1. Bu projeyi klonlayın veya indirin.
2. Proje dizinine gidin ve aşağıdaki komutu çalıştırarak derleyin:
   ```bash
   gcc -o acil_servis acil_servis.c
   ```

## Kullanım

1. Uygulamayı başlatmak için aşağıdaki komutu çalıştırın:
   ```bash
   ./acil_servis
   ```

2. Ana menüde aşağıdaki seçenekler sunulacaktır:
   ```
   --- ACİL SERVİS SİSTEMİ ---
   1. Hasta Ekle
   2. Reçete Numarası Üret
   3. Hasta Bilgilerini Görüntüle
   4. Hastaları Listele
   5. Hasta Sil
   6. Çıkış
   ```

### 1. Hasta Ekle

- Hasta bilgilerini girerek yeni bir hasta ekleyin.

### 2. Reçete Numarası Üret

- Rastgele bir reçete numarası üretin ve bir hastaya atayın.

### 3. Hasta Bilgilerini Görüntüle

- Hasta ID'sini girerek hasta bilgilerini görüntüleyin.

### 4. Hastaları Listele

- Tüm hastaları öncelik seviyelerine göre listeleyin.

### 5. Hasta Sil

- Hasta ID'sini girerek bir hastayı silin.

### 6. Çıkış

- Uygulamadan çıkın.

## Geliştirici Notları

- Bu uygulama, dinamik bellek tahsisi kullanarak hasta bilgilerini yönetir.
- Bellek sızıntılarını önlemek için program sonunda tüm dinamik bellek alanları serbest bırakılır.
- Kod, kullanıcıdan alınan girişleri işlemek ve hataları ele almak için çeşitli kontroller içerir.

## Katkıda Bulunma

Katkıda bulunmak isterseniz, lütfen bir pull request gönderin veya bir issue açın.

## Lisans

Bu proje MIT Lisansı altında lisanslanmıştır.
