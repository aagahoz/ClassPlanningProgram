#ifndef library_h_
#define library_h_

#include <stdio.h>				// scanf printf sprintf fscanf fclose fprintf
#include <locale.h>				// setlocale
#include <string.h>				// strcmp strcpy

struct ogrInfo{		// genel öðrenci bilgilerini tutan struct yapýsý
    long long int numara;
    char isim[50];
    char soyisim[50];
    char harf_not[2];
    int harfNotu;
};

struct asistInfo{	// genel asistan bilgilerini tutan struct yapýsý
    char isim[50];
    char soyisim[50];
    int kapasite;
};

struct dersInfo{	// genel ders bilgilerini tutan struct yapýsý
    char isim[10];
    char ogretmen_adi[15];
    char ogretmen_soyadi[15];
    char ogretmen_mail[20];
    char dersZamani[100];
};


void Duzeltme(FILE *oku, FILE *yaz,int *pointer,struct dersInfo ders);		// numara sýrasýna göre sýralama	// tekrar eden öðrenciler listeden çýkartma
void ogrenciEkle(FILE *ekle,int *pointer,struct dersInfo ders);				// listeye ve dosyaya yeni öðrenci ekleme
int ogrenciCikar(FILE *yaz,FILE *oku,int *pointer,struct dersInfo ders);	// numarasý girilen öðrenci çýkartýlýp listenin ve dosyanýn yenilenmesi

void sinifOlusturma(FILE *oku,int ogrSay,struct dersInfo ders);				// sýnýf özelliklerine göre öðrenci listesinden sýnýf oluþturma
void asistanBolme(FILE *oku,int ogrSay,struct dersInfo ders);				// asistanlara eþit sayýda öðrenci daðýtma
void NotBolme(FILE *oku,int ogrSay,FILE *yaz1,FILE *yaz2,struct dersInfo ders);					// önceki dersini geçme notuna göre sýralama ve sýnýflandýrma
void NotBolme2(FILE *oku,int ogrSay,FILE *yaz1,FILE *yaz2,FILE *yaz3,struct dersInfo ders);		// önceki dersini geçme notuna göre sýralama ve sýnýflandýrma
struct dersInfo *bilgiAlma(FILE *okuInfo, struct dersInfo *ders);								// derslerle alakalý bilgileri ilgili dosyadan alýr ve ram de tutar
void bilgiVerme(struct dersInfo ders);															// derslerle alakalý bilgileri ekrana basar

#endif
