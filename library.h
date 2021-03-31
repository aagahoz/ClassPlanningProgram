#ifndef library_h_
#define library_h_

#include <stdio.h>				// scanf printf sprintf fscanf fclose fprintf
#include <locale.h>				// setlocale
#include <string.h>				// strcmp strcpy

struct ogrInfo{		// genel ��renci bilgilerini tutan struct yap�s�
    long long int numara;
    char isim[50];
    char soyisim[50];
    char harf_not[2];
    int harfNotu;
};

struct asistInfo{	// genel asistan bilgilerini tutan struct yap�s�
    char isim[50];
    char soyisim[50];
    int kapasite;
};

struct dersInfo{	// genel ders bilgilerini tutan struct yap�s�
    char isim[10];
    char ogretmen_adi[15];
    char ogretmen_soyadi[15];
    char ogretmen_mail[20];
    char dersZamani[100];
};


void Duzeltme(FILE *oku, FILE *yaz,int *pointer,struct dersInfo ders);		// numara s�ras�na g�re s�ralama	// tekrar eden ��renciler listeden ��kartma
void ogrenciEkle(FILE *ekle,int *pointer,struct dersInfo ders);				// listeye ve dosyaya yeni ��renci ekleme
int ogrenciCikar(FILE *yaz,FILE *oku,int *pointer,struct dersInfo ders);	// numaras� girilen ��renci ��kart�l�p listenin ve dosyan�n yenilenmesi

void sinifOlusturma(FILE *oku,int ogrSay,struct dersInfo ders);				// s�n�f �zelliklerine g�re ��renci listesinden s�n�f olu�turma
void asistanBolme(FILE *oku,int ogrSay,struct dersInfo ders);				// asistanlara e�it say�da ��renci da��tma
void NotBolme(FILE *oku,int ogrSay,FILE *yaz1,FILE *yaz2,struct dersInfo ders);					// �nceki dersini ge�me notuna g�re s�ralama ve s�n�fland�rma
void NotBolme2(FILE *oku,int ogrSay,FILE *yaz1,FILE *yaz2,FILE *yaz3,struct dersInfo ders);		// �nceki dersini ge�me notuna g�re s�ralama ve s�n�fland�rma
struct dersInfo *bilgiAlma(FILE *okuInfo, struct dersInfo *ders);								// derslerle alakal� bilgileri ilgili dosyadan al�r ve ram de tutar
void bilgiVerme(struct dersInfo ders);															// derslerle alakal� bilgileri ekrana basar

#endif
