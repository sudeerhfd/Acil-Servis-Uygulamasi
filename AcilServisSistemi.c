#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_RECETE 100

// Hasta bilgileri icin struct
typedef struct Hasta {
    char *id; // Dinamik olarak tahsis edilmis hasta ID'si
    char *ad;
    int yas;
    char *durum;
    int oncelik; // 1: Yuksek, 2: Orta, 3: Dusuk
    char *doktorAd; // Doktor adi
    char *doktorSoyad; // Doktor soyadi
    char *doktorUnvan; // Doktor unvani
    char *acilIslem; // Acil islemler (ornegin, tetkik, mudahale)
    char *cikisTarihi; // cikis tarihi ve saati
    char *yontem; // Yonlendirilecegi islem (Goruntuleme / Cerrahi)
    char *bolge; // Yonlendirilecegi bolge (Yesil, Sari, Kirmizi)
    char *yonlendirilenBolum; // Yonlendirilen bolum
    int doktorOnay; // 1: Onay verildi, 0: Onay verilmedi
    int receteNumarasi; // Hastanin recete numarasi
    struct Hasta *next; // Bagli liste icin sonraki hasta
} Hasta;

// Kuyruk yapisi
typedef struct {
    Hasta *front; // Kuyrugun on tarafý, ilk hasta
    Hasta *rear;  // Kuyrugun arka tarafý, son hasta
} Queue;

// Yeni kuyruk olusturma fonksiyonu
Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

// Hasta ekleme fonksiyonu
void enqueue(Queue* q, Hasta* h) {
    if (q->rear == NULL) {
        q->front = q->rear = h;
        return;
    }
    q->rear->next = h;
    q->rear = h;
}

// Hasta cikarma fonksiyonu
Hasta* dequeue(Queue* q) {
    if (q->front == NULL) {
        return NULL;
    }
    Hasta* temp = q->front;
    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }
    return temp;
}

// Recete numaralari dizisi
int receteNumaralari[MAX_RECETE];
int receteSayisi = 0;

// Yuksek, orta ve dusuk oncelikli kuyruklar
Queue *yuksekOncelik, *ortaOncelik, *dusukOncelik;

// Yeni hasta ekleme fonksiyonu
void hastaEkle() {
    Hasta* yeniHasta = (Hasta*)malloc(sizeof(Hasta));
    if (yeniHasta == NULL) {
        printf("Bellek tahsisi hatasi!\n");
        return;
    }

    // Hasta bilgilerini al
    yeniHasta->id = (char *)malloc(10 * sizeof(char));
    printf("Hasta ID (HL7 formatinda): ");
    scanf("%s", yeniHasta->id);
    getchar();

    yeniHasta->ad = (char *)malloc(50 * sizeof(char));
    printf("Hasta Adi: ");
    fgets(yeniHasta->ad, 50, stdin);
    yeniHasta->ad[strcspn(yeniHasta->ad, "\n")] = 0;

    printf("Yas: ");
    scanf("%d", &yeniHasta->yas);
    getchar();

    yeniHasta->durum = (char *)malloc(100 * sizeof(char));
    printf("Hastalik Durumu: ");
    fgets(yeniHasta->durum, 100, stdin);
    yeniHasta->durum[strcspn(yeniHasta->durum, "\n")] = 0;

    yeniHasta->doktorAd = (char *)malloc(50 * sizeof(char));
    yeniHasta->doktorSoyad = (char *)malloc(50 * sizeof(char));
    yeniHasta->doktorUnvan = (char *)malloc(50 * sizeof(char));

    printf("Doktor Adi: ");
    fgets(yeniHasta->doktorAd, 50, stdin);
    yeniHasta->doktorAd[strcspn(yeniHasta->doktorAd, "\n")] = 0;

    printf("Doktor Soyadi: ");
    fgets(yeniHasta->doktorSoyad, 50, stdin);
    yeniHasta->doktorSoyad[strcspn(yeniHasta->doktorSoyad, "\n")] = 0;

    printf("Doktor Unvani: ");
    fgets(yeniHasta->doktorUnvan, 50, stdin);
    yeniHasta->doktorUnvan[strcspn(yeniHasta->doktorUnvan, "\n")] = 0;

    yeniHasta->acilIslem = (char *)malloc(100 * sizeof(char));
    printf("Acil islem: ");
    fgets(yeniHasta->acilIslem, 100, stdin);
    yeniHasta->acilIslem[strcspn(yeniHasta->acilIslem, "\n")] = 0;

    int oncelikGiris;
    do {
        printf("oncelik (1:Yuksek, 2:Orta, 3:Dusuk): ");
        scanf("%d", &oncelikGiris);
        getchar();

        if (oncelikGiris >= 1 && oncelikGiris <= 3) {
            yeniHasta->oncelik = oncelikGiris;
            break;
        } else {
            printf("Gecersiz oncelik! Lutfen 1, 2 veya 3 giriniz.\n");
        }
    } while (1);

    // Hastayi uygun oncelik kuyruðuna ekle
    yeniHasta->next = NULL;
    if (yeniHasta->oncelik == 1) {
        enqueue(yuksekOncelik, yeniHasta);
        yeniHasta->bolge = "Kirmizi";
    } else if (yeniHasta->oncelik == 2) {
        enqueue(ortaOncelik, yeniHasta);
        yeniHasta->bolge = "Sari";
    } else {
        enqueue(dusukOncelik, yeniHasta);
        yeniHasta->bolge = "Yesil";
    }

    // Hastanin yonlendirilmesi
    if (yeniHasta->oncelik == 1) {
        printf("Acil hasta yonlendirme secenekleri:\n");
        printf("1.  Goruntuleme\n");
        printf("2.  Ortopedi\n");
        printf("3.  Genel Cerrahi\n");
        printf("4.  Kardiyoloji\n");
        printf("5.  Noroloji\n");
        printf("6.  Dahiliye\n");
        printf("7.  Cocuk Acili\n");
        printf("8.  Plastik Cerrahi\n");
        printf("9.  Goz Hastaliklari\n");
        printf("10. Kulak Burun Bogaz\n");
        printf("11. uroloji\n");
        printf("12. Kadin Hastaliklari ve Dogum\n");
        printf("13. Psikiyatri\n");
        printf("14. Bolume yonlendirmeye gerek yok.\n");
        printf("Bir bolum secin:\n");
        int bolumSecim;
        scanf("%d", &bolumSecim);
        getchar();

        switch (bolumSecim) {
            case 1:
                yeniHasta->yonlendirilenBolum = "Goruntuleme";
                break;
            case 2:
                yeniHasta->yonlendirilenBolum = "Ortopedi";
                break;
            case 3:
                yeniHasta->yonlendirilenBolum = "Genel Cerrahi";
                break;
            case 4:
                yeniHasta->yonlendirilenBolum = "Kardiyoloji";
                break;
            case 5:
                yeniHasta->yonlendirilenBolum = "Noroloji";
                break;
            case 6:
                yeniHasta->yonlendirilenBolum = "Dahiliye";
                break;
            case 7:
                yeniHasta->yonlendirilenBolum = "Cocuk Acili";
                break;
            case 8:
                yeniHasta->yonlendirilenBolum = "Plastik Cerrahi";
                break;
            case 9:
                yeniHasta->yonlendirilenBolum = "Goz Hastaliklari";
                break;
            case 10:
                yeniHasta->yonlendirilenBolum = "Kulak Burun Bogaz";
                break;
            case 11:
                yeniHasta->yonlendirilenBolum = "Uroloji";
                break;
            case 12:
                yeniHasta->yonlendirilenBolum = "Kadin Hastaliklari ve Dogum";
                break;
            case 13:
                yeniHasta->yonlendirilenBolum = "Psikiyatri";
                break;
            case 14:
                yeniHasta->yonlendirilenBolum = "Bolume yonlendirmeye gerek yok.";
                break;
            default:
                printf("Gecersiz bolum secimi!\n");
                yeniHasta->yonlendirilenBolum = "Belirtilmemis";
        }
    } else {
        if (strstr(yeniHasta->durum, "ihtiyac yok") != NULL) {
            printf("Hastanin bir bolume yonlendirilmesine gerek yok.\n");
            yeniHasta->yonlendirilenBolum = "Yonlendirilmedi";
        }
    }

    printf("Doktor onayini aliniz. Onay verildi mi? (1: Evet, 0: Hayir): ");
    scanf("%d", &yeniHasta->doktorOnay);
    getchar();

    if (yeniHasta->doktorOnay) {
        printf("Hasta cikisi onaylandi.\n");
    } else {
        printf("Hasta cikisi onaylanmadi.\n");
    }

    printf("Hasta basariyla kaydedildi! Bolge: %s, Yonlendirilen Bolum: %s\n\n", yeniHasta->bolge, yeniHasta->yonlendirilenBolum);
}

// Recete numarasi uretme fonksiyonu
void receteNumarasiUret() {
    if (receteSayisi < MAX_RECETE) {
        receteNumaralari[receteSayisi] = rand() % 10000 + 1000;
        printf("Yeni recete numarasi: %d\n", receteNumaralari[receteSayisi]);

        char hastaID[10];
        printf("Bu recete numarasini hangi hasta ID'sine atamak istiyorsunuz? ");
        scanf("%s", hastaID);
        getchar();

        Hasta* current = yuksekOncelik->front;
        while (current != NULL) {
            if (strcmp(current->id, hastaID) == 0) {
                current->receteNumarasi = receteNumaralari[receteSayisi];
                printf("Hasta ID: %s icin recete numarasi %d atandi.\n", hastaID, receteNumaralari[receteSayisi]);
                receteSayisi++;
                return;
            }
            current = current->next;
        }

        current = ortaOncelik->front;
        while (current != NULL) {
            if (strcmp(current->id, hastaID) == 0) {
                current->receteNumarasi = receteNumaralari[receteSayisi];
                printf("Hasta ID: %s icin recete numarasi %d atandi.\n", hastaID, receteNumaralari[receteSayisi]);
                receteSayisi++;
                return;
            }
            current = current->next;
        }

        current = dusukOncelik->front;
        while (current != NULL) {
            if (strcmp(current->id, hastaID) == 0) {
                current->receteNumarasi = receteNumaralari[receteSayisi];
                printf("Hasta ID: %s icin recete numarasi %d atandi.\n", hastaID, receteNumaralari[receteSayisi]);
                receteSayisi++;
                return;
            }
            current = current->next;
        }

        printf("Hasta ID'si bulunamadi.\n");
    } else {
        printf("Recete numarasi uretilemedi, kapasite dolmus!\n");
    }
}

// Hasta bilgilerini goruntuleme fonksiyonu
void hastaBilgisi() {
    char hastaID[10];
    printf("Hasta ID'sini girin: ");
    scanf("%s", hastaID);
    getchar();

    Hasta* current = yuksekOncelik->front;
    while (current != NULL) {
        if (strcmp(current->id, hastaID) == 0) {
            printf("Hasta Bilgileri (Yuksek Oncelik):\n");
            printf("ID: %s\nAd: %s\nYas: %d\nDurum: %s\n", current->id, current->ad, current->yas, current->durum);
            return;
        }
        current = current->next;
    }

    current = ortaOncelik->front;
    while (current != NULL) {
        if (strcmp(current->id, hastaID) == 0) {
            printf("Hasta Bilgileri (Orta Oncelik):\n");
            printf("ID: %s\nAd: %s\nYas: %d\nDurum: %s\n", current->id, current->ad, current->yas, current->durum);
            return;
        }
        current = current->next;
    }

    current = dusukOncelik->front;
    while (current != NULL) {
        if (strcmp(current->id, hastaID) == 0) {
            printf("Hasta Bilgileri (Dusuk Oncelik):\n");
            printf("ID: %s\nAd: %s\nYas: %d\nDurum: %s\n", current->id, current->ad, current->yas, current->durum);
            return;
        }
        current = current->next;
    }

    printf("Hasta bulunamadi.\n");
}

// Hastalari listeleme fonksiyonu
void hastaListele() {
    Hasta* current;

    printf("Yuksek Oncelikli Hastalar:\n");
    current = yuksekOncelik->front;
    while (current != NULL) {
        printf("ID: %s, Ad: %s, Yas: %d, Durum: %s, Oncelik: %d, Doktor Adi: %s, Bolge: %s, Yonlendirilen Bolum: %s, Recete Numarasi: %d\n",
               current->id, current->ad, current->yas, current->durum, current->oncelik, current->doktorAd, current->bolge, current->yonlendirilenBolum, current->receteNumarasi);
        current = current->next;
    }

    printf("\nOrta Oncelikli Hastalar:\n");
    current = ortaOncelik->front;
    while (current != NULL) {
        printf("ID: %s, Ad: %s, Yas: %d, Durum: %s, Oncelik: %d, Doktor Adi: %s, Bolge: %s, Yonlendirilen Bolum: %s, Recete Numarasi: %d\n",
               current->id, current->ad, current->yas, current->durum, current->oncelik, current->doktorAd, current->bolge, current->yonlendirilenBolum, current->receteNumarasi);
        current = current->next;
    }

    printf("\nDusuk Oncelikli Hastalar:\n");
    current = dusukOncelik->front;
    while (current != NULL) {
        printf("ID: %s, Ad: %s, Yas: %d, Durum: %s, Oncelik: %d, Doktor Adi: %s, Bolge: %s, Yonlendirilen Bolum: %s, Recete Numarasi: %d\n",
               current->id, current->ad, current->yas, current->durum, current->oncelik, current->doktorAd, current->bolge, current->yonlendirilenBolum, current->receteNumarasi);
        current = current->next;
    }
}

// Hasta silme fonksiyonu
void hastaSil() {
    char hastaID[10];
    printf("Silmek istediginiz hasta ID'sini girin: ");
    scanf("%s", hastaID);
    getchar();

    Hasta *current, *prev;

    current = yuksekOncelik->front;
    prev = NULL;
    while (current != NULL) {
        if (strcmp(current->id, hastaID) == 0) {
            if (prev == NULL) {
                yuksekOncelik->front = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == yuksekOncelik->rear) {
                yuksekOncelik->rear = prev;
            }
            free(current->id);
            free(current->ad);
            free(current->durum);
            free(current->doktorAd);
            free(current->doktorSoyad);
            free(current->doktorUnvan);
            free(current->acilIslem);
            free(current);
            printf("Hasta basariyla silindi.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    current = ortaOncelik->front;
    prev = NULL;
    while (current != NULL) {
        if (strcmp(current->id, hastaID) == 0) {
            if (prev == NULL) {
                ortaOncelik->front = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == ortaOncelik->rear) {
                ortaOncelik->rear = prev;
            }
            free(current->id);
            free(current->doktorSoyad);
            free(current->doktorUnvan);
            free(current->acilIslem);
            free(current);
            printf("Hasta basariyla silindi.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    current = dusukOncelik->front;
    prev = NULL;
    while (current != NULL) {
        if (strcmp(current->id, hastaID) == 0) {
            if (prev == NULL) {
                dusukOncelik->front = current->next;
            } else {
                prev->next = current->next;
            }
            if (current == dusukOncelik->rear) {
                dusukOncelik->rear = prev;
            }
            free(current->id);
            free(current->ad);
            free(current->durum);
            free(current->doktorAd);
            free(current->doktorSoyad);
            free(current->doktorUnvan);
            free(current->acilIslem);
            free(current);
            printf("Hasta basariyla silindi.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("Hasta bulunamadi.\n");
}

// Ana menu
int main() {
    yuksekOncelik = createQueue();
    ortaOncelik = createQueue();
    dusukOncelik = createQueue();

    int secim;

    do {
        printf("\n--- Hastane Yonetim Sistemi ---\n");
        printf("1. Hasta Ekle\n");
        printf("2. Recete Numarasi Uret\n");
        printf("3. Hasta Bilgilerini Goruntule\n");
        printf("4. Hastalari Listele\n");
        printf("5. Hasta Sil\n");
        printf("6. Cikis\n");
        printf("Seciminizi yapin: ");
        scanf("%d", &secim);
        getchar();

        switch (secim) {
            case 1:
                hastaEkle();
                break;
            case 2:
                receteNumarasiUret();
                break;
            case 3:
                hastaBilgisi();
                break;
            case 4:
                hastaListele();
                break;
            case 5:
                hastaSil();
                break;
            case 6:
                printf("Cikiliyor...\nCikis yapildi\n");
                break;
            default:
                printf("Gecersiz secim! Lutfen tekrar deneyin.\n");
        }
    } while (secim != 6);

    // Program sonunda tum dinamik bellek alanlarini serbest birak
    Hasta* current;

    while ((current = dequeue(yuksekOncelik)) != NULL) {
        free(current->id);
        free(current->ad);
        free(current->durum);
        free(current->doktorAd);
        free(current->doktorSoyad);
        free(current->doktorUnvan);
        free(current->acilIslem);
        free(current);
    }
    free(yuksekOncelik);

    while ((current = dequeue(ortaOncelik)) != NULL) {
        free(current->id);
        free(current->ad);
        free(current->durum);
        free(current->doktorAd);
        free(current->doktorSoyad);
        free(current->doktorUnvan);
        free(current->acilIslem);
        free(current);
    }
    free(ortaOncelik);

    while ((current = dequeue(dusukOncelik)) != NULL) {
        free(current->id);
        free(current->ad);
        free(current->durum);
        free(current->doktorAd);
        free(current->doktorSoyad);
        free(current->doktorUnvan);
        free(current->acilIslem);
        free(current);
    }
    free(dusukOncelik);

    return 0;
}
