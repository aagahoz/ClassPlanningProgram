#include "library.h"
// VER�LER�N TEMEL DOSYADAN OKUNMASI
void Duzeltme(FILE *oku, FILE *yaz,int *ogrSay,struct dersInfo ders){
    struct ogrInfo tablo [500];
    //struct ogrInfo *tablo;
	//tablo=(struct ogrInfo *)malloc(sizeof(struct ogrInfo));
	int temp=0;
    int say = 0, i=0,j=0;
    
    while (!feof(oku) )
    {
        fscanf(oku,"%lld %s %s %s\n",&tablo[say].numara,&tablo[say].isim,&tablo[say].soyisim,&tablo[say].harf_not);
        say++;
    }
//  ��RENC�LER�N NUMARASINA G�RE L�STEN�N YEN�DEN SIRALANMASI
    long long int tempNu;
    char tempIsim[50];
    char tempSoyisim[50];
    char tempNot[3];
	for (i=0; i<say-1; i++)
    {
        for (j=i+1; j<say-1; j++)
        {
            if (tablo[i].numara>=tablo[j].numara)
            {
                tempNu=tablo[i].numara;
                strcpy(tempIsim,tablo[i].isim);
                strcpy(tempSoyisim,tablo[i].soyisim);
                strcpy(tempNot,tablo[i].harf_not);

                tablo[i].numara=tablo[j].numara;
                strcpy(tablo[i].isim,tablo[j].isim);
                strcpy(tablo[i].soyisim,tablo[j].soyisim);
                strcpy(tablo[i].harf_not,tablo[j].harf_not);

                tablo[j].numara=tempNu;
                strcpy(tablo[j].isim,tempIsim);
                strcpy(tablo[j].soyisim,tempSoyisim);
                strcpy(tablo[j].harf_not,tempNot);
            }
        }
    } 
 // E�ER L�STEDE ADI �OK KEZ GE�EN VARSA FAZLALIKLARIN L�STEDEN ATILMASI VE �S�MLER�N�N EKRANA BASILMASI
    printf("%s dersi listesinde tekrar eden kayitlar:\n",ders.isim);
    
	i=0;j=0; int sayac = 0;
    for (j = i+1; j<say-1; j++)
    {
        if (tablo[i].numara == tablo[j].numara)
        {
            printf("-%-10s %-s\n",tablo[j].isim, tablo[j].soyisim);
            sayac++;
        }
        else
        {
            fprintf(yaz,"%13lld %13s %13s %13s\n",tablo[i].numara,tablo[i].isim, tablo[i].soyisim,tablo[i].harf_not);
        }
        i++;
    }
    printf("\n");
   	*ogrSay = say-sayac-1;
}
//------------------------------------------------------------------------------------------------------------------------------------------
// L�STEYE YEN� ��RENC� EKLENMES�
void ogrenciEkle(FILE *ekle,int *ogrSay,struct dersInfo ders){
    struct ogrInfo tablo[2];
    int say=0;
    
// KAYDED�LECEK ��RENC�N�N B�LG�LER�N�N KULLANICIDAN ALINMASI
        printf("Ogrencinin numarasini giriniz >> ");
        scanf("%lld",&tablo[say].numara);
        printf("Ogrencinin adini giriniz >> ");
        scanf("%s",&tablo[say].isim);
        printf("Ogrencinin soyismini giriniz >> ");
        scanf("%s",&tablo[say].soyisim);
		printf("Ogrencinin %s harf notunu giriniz >> ",ders.isim);
        scanf("%s",&tablo[say].harf_not);

// ALINAN B�LG�LER�N DOSYANIN EN SONUNA KAYDED�LMES�
		fprintf(ekle,"%13lld %13s %13s %13s",tablo[say].numara,tablo[say].isim,tablo[say].soyisim,tablo[say].harf_not);
        printf("%s dersi listesine ��renci ba�ar�yla eklendi!\n\n",ders.isim);
        *ogrSay += 1;
}
//------------------------------------------------------------------------------------------------------------------------------------------
//  L�STEDEN ��RENC� �IKARTILIP YEN� L�STE OLU�TURULMASI
int ogrenciCikar(FILE *yaz,FILE *oku,int *ogrSay,struct dersInfo ders){
    struct ogrInfo tablo[500];
    int say=0,i,j;
    int sira=-1;
    long long int istekNo=0;
	int ogrenciSay = *ogrSay;
// VER�LER�N DOSYADAN ALINMASI

	    while (ogrenciSay)
        {
            fscanf(oku,"%lld %s %s %s",&tablo[say].numara,&tablo[say].isim,&tablo[say].soyisim,&tablo[say].harf_not);
            say++;
        	ogrenciSay--;
        }
        
// �IKARTILACAK ��RENC�N�N NUMARASININ ALINMASI 
        printf("Lutfen %s dersi listesinden ��karmak istedi�iniz ��rencinin numaras�n� giriniz >> ",ders.isim);
        scanf("%lld",&istekNo);
// ��RENC� NUMARASINA G�RE L�STEDE SIRA NUMARASI ARAMASI    
        for(i=0;i<say;i++)
		{
        	if (tablo[i].numara == istekNo){
        		printf("%s listesinden ��renci bulundu!\n",ders.isim);
        		sira = i;
        		say--;
			}
		}
		if(sira == -1)
		{
			printf("��renci bulunamad�!\n");
			return 0;
		}
// YEN� L�STE OLU�TURULURKEN BEL�RLENEN ��RENC� HAR�C� T�M ��RENC�LER�N DOSYAYA YAZILMASI
    for (j=0; j<say; j++)
    {
    	if(j==sira)
		{
			continue;
		}
		else
		{
    	fprintf(yaz,"%13lld %13s %13s %13s\n",tablo[j].numara,tablo[j].isim, tablo[j].soyisim,tablo[j].harf_not);
   		}
    }
	printf("��renci ba�ar�yla ��kar�ld�!\n\n");
	*ogrSay -= 1;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void sinifOlusturma(FILE *oku,int ogrSay,struct dersInfo ders){
	
    int toplam=0,ortalama,sinifSayisi;
    int i,j,temp,a;
    struct ogrInfo tablo[500];
    int say=0;
	int ogrenciSay = ogrSay;
    while(ogrenciSay)
    {
        fscanf(oku,"%lld %s %s %s",&tablo[say].numara,&tablo[say].isim,&tablo[say].soyisim,&tablo[say].harf_not);
        say++;
        ogrenciSay--;
    }
    ogrSay=say;
	printf("%s dersi i�in ��renci say�s� toplam :  %d\n\n",ders.isim,ogrSay);
	
// Sinif islemleri
    printf("%s dersi i�in kullan�labilicek s�n�f sayisini giriniz >> ",ders.isim);
    scanf("%d",&sinifSayisi);
    int dizi[sinifSayisi];
    int diziDiger[sinifSayisi];
// Sinif kapasitesi isteme
    for (i=0; i<sinifSayisi; i++)
    {
        printf("S�n�f kapasitesini giriniz >> ");
        scanf("%d",&dizi[i]);
        toplam=toplam+dizi[i];
    }
// Toplam ogrenciden kapasite az olamaz
    if(ogrSay>toplam)
    {
        printf("L�tfen kapasiteyi b�y�k girin:\n\n");
        printf("%s dersi i�in kullan�labilicek sinif sayisini tekrar giriniz >> ",ders.isim);
        scanf("%d",&sinifSayisi);
        int dizi[sinifSayisi];
        int diziDiger[sinifSayisi];
//  Sinif kapasitesi isteme
        for (i=0; i<sinifSayisi; i++)
        {
            printf("S�n�f kapasitesini giriniz  >> ");
            scanf("%d",&dizi[i]);
            toplam=toplam+dizi[i];
        }
    }
    for(i=0; i<sinifSayisi; i++)
    {
        diziDiger[i]=dizi[i];
    }

// Sinif Siralamasi Kucukten Buyuge
    for(i=0; i<sinifSayisi; i++)
    {
        for(j=0; j<sinifSayisi; j++)
        {
            if (dizi[i]<=dizi[j])
            {
                temp=dizi[i];
                dizi[i]=dizi[j];
                dizi[j]=temp;
            }
        }
    }

//Sinif siralamasi buyukten kucuge
    for(i=0; i<sinifSayisi; i++)
    {
        for(j=0; j<sinifSayisi; j++)
        {
            if (diziDiger[i]>=diziDiger[j])
            {
                temp=diziDiger[i];
                diziDiger[i]=diziDiger[j];
                diziDiger[j]=temp;
            }
        }
    }

// Dosyalara cikarmak icin kayit sayilarini dizilere attik
    int genel_say[sinifSayisi];
// S�n�flardaki ogrenciler yaz�lacak
    printf(">> E�it da��l�ml� s�n�f i�in 1'e ,  En az s�n�f i�in herhangi bir say�ya bas�n�z >> ");
    scanf("%d",&a);
    int kalan=0;
	printf("\n");
    if(a==1)
    {
        for(i=0; i<sinifSayisi; i++)
        {
            ortalama=ogrSay/(sinifSayisi-i);
            if(ortalama<=dizi[i])
            {
                printf("%d. s�n�fta %d kisi vard�r\n",i+1,ortalama);
                genel_say[i]=ortalama;
                ogrSay-=ortalama;
            }
            else
            {
                printf("%d. s�n�fta %d ki�i vard�r\n",i+1,dizi[i]);
                genel_say[i]=dizi[i];
                ogrSay-=dizi[i];
            }
        }
    }
    else
    {
        for(i=0; i<sinifSayisi; i++)
        {
            if(ogrSay>diziDiger[i])
            {
                printf("%d. s�n�fta %d ki�i vard�r\n",i+1,diziDiger[i]);
                genel_say[i]=diziDiger[i];
                ogrSay=ogrSay-diziDiger[i];
            }
            else
            {
                printf("%d. s�n�fta %d ki�i vard�r\n",i+1,ogrSay);
                genel_say[i]=ogrSay;
// dagilim yaparken dizinin di�er elemanlari default oldu�undan sifir atandi
                int a=0;
                for(a=i;a<sinifSayisi;a++){
                    genel_say[a]=0;
                }
                printf("\n>> Bundan sonraki s�n�flarda ��renci bulunmamaktad�r\n");
                break;
            }
        }
    }
    FILE *dagilim[sinifSayisi];
    char dosya[30];
    for(i=1; i<=sinifSayisi; i++)
    {
        sprintf(dosya,"%s%d%s%c","sinif",i,".txt",'\0');
        dagilim[i]=fopen(dosya,"w");
    }
    int z=0,m;
	for (i=1; i<=sinifSayisi; i++){
    	fprintf(dagilim[i],"%15s %15s %15s %12s Not\n","Numara","�sim","Soyisim",ders.isim);
	}
	for (i=1; i<=sinifSayisi; i++)
    {
        for (m=1; m<=genel_say[i-1]; m++)
        {
            fscanf(oku,"%lld %s %s %s",&tablo[z].numara,&tablo[z].isim,&tablo[z].soyisim,&tablo[z].harf_not);
            fprintf(dagilim[i],"%15lld %15s %15s %10s\n",tablo[z].numara,tablo[z].isim,tablo[z].soyisim,tablo[z].harf_not);
            z++;
            if (z==ogrSay)
				 m=genel_say[i-1]+2;
        }
    }
    for(i=1; i<=sinifSayisi; i++)
    {
        fclose(dagilim[i]);
    }
	printf("\nS�n�flar ba�ar�yla Olu�turuldu!\n\n");
}
//--------------------------------------------------------------------------------------------------------------------------
void asistanBolme(FILE *oku,int ogrSay,struct dersInfo ders){
	struct asistInfo asistan[10];
    int toplam=0,ortalama,asistanSayisi;
    int i,j,temp,a;
    int tempc[15];
    struct ogrInfo tablo[500];
    int say=0;
    
    while(ogrSay)
    {
        fscanf(oku,"%lld %s %s %s",&tablo[say].numara,&tablo[say].isim,&tablo[say].soyisim,&tablo[say].harf_not);
        say++;
        ogrSay--;
    }
    
    ogrSay=say;
	printf("��renci say�s� toplam :  %d\n\n",ogrSay);
	
//	Sinif islemleri
    printf("Asistan sayisini giriniz:");							
    scanf("%d",&asistanSayisi);
// Sinif kapasitesi isteme
    for (i=0; i<asistanSayisi; i++)
    {
    	printf("Asistan ad�n� giriniz >> ");
        scanf("%s",&asistan[i].isim);
    	printf("Asistan soyad�n� giriniz >> ");
        scanf("%s",&asistan[i].soyisim);
    	printf("Asistan�n alabilece�i maksimum ��renci say�s�n� giriniz >> ");
        scanf("%s",&asistan[i].kapasite);
        toplam=toplam+asistan[i].kapasite;
    }
//	Toplam ogrenciden kapasite az olamaz
    if(ogrSay>toplam)
    {
    	printf("Asistan sayisini giriniz >> ");							
    	scanf("%d",&asistanSayisi);
    	/** Sinif kapasitesi isteme **/
	    for (i=0; i<asistanSayisi; i++)
	    {
	    	printf("Asistan ad�n� giriniz >> ");
	        scanf("%s",&asistan[i].isim);
	    	printf("Asistan soyad�n� giriniz >> ");
	        scanf("%s",&asistan[i].soyisim);
	    	printf("Asistan�n alabilece�i maksimum ��renci say�s�n� giriniz >> ");
	        scanf("%s",&asistan[i].kapasite);
	        toplam=toplam+asistan[i].kapasite;
	        }
    }
//	Dosyalara cikarmak icin kayit sayilarini dizilere attik
    int genel_say[asistanSayisi];
    printf(">> Asistanlara e�it da��l�m yap�ld�!\n\n");
    int kalan=0;
	printf("\n");
        for(i=0; i<asistanSayisi; i++)
        {
            ortalama=ogrSay/(asistanSayisi-i);
            if(ortalama<=asistan[i].kapasite)
            {
                printf("%s %s isimli asistanda %d kisi vard�r\n",asistan[i].isim,asistan[i].soyisim,ortalama);
                genel_say[i]=ortalama;
                ogrSay-=ortalama;
            }
            else
            {
                printf("%s %s isimli asistanda %d ki�i vard�r\n",asistan[i].isim,asistan[i].soyisim,asistan[i].kapasite);
                genel_say[i]=asistan[i].kapasite;
                ogrSay-=asistan[i].kapasite;
            }
        }
    FILE *dagilim[asistanSayisi];
    char dosya[30];
    for(i=1; i<=asistanSayisi; i++)
    {
        sprintf(dosya,"%s_%s%s%c",asistan[i].isim,asistan[i].soyisim,".txt",'\0');
        dagilim[i]=fopen(dosya,"w");
    }
    int z=0,m;
    
	for (i=1; i<=asistanSayisi; i++){
    	fprintf(dagilim[i],"%15s %15s %15s %12s Not\n","Numara","�sim","Soyisim",ders.isim);
	}
	
    for (i=1; i<=asistanSayisi; i++)
    {
        for (m=1; m<=genel_say[i-1]; m++)
        {
            fscanf(oku,"%d %s %s %s",&tablo[z].numara,&tablo[z].isim,&tablo[z].soyisim,&tablo[z].harf_not);
            fprintf(dagilim[i],"%15d %15s %15s %10s\n",tablo[z].numara,tablo[z].isim,tablo[z].soyisim,tablo[z].harf_not);
            z++;
            if (z==ogrSay)
				 m=genel_say[i-1]+2;
        }
    }
    for(i=1; i<=asistanSayisi; i++)
    {
        fclose(dagilim[i]);
    }
	printf("\nAsistanlara ��renciler ba�ar�yla da��t�ld� ve dosyaya kaydedildi!\n\n");
}
//------------------------------------------------------------------------------------------------------------------------------------------------------
void NotBolme(FILE *oku,int ogrSay,FILE *yaz1,FILE *yaz2,struct dersInfo ders){
/*
	AA: 1	BA: 1	BB:1 
	CB: 2	CC: 2   DC: 3	DD:3
*/
    int toplam=0,ortalama,sinifSayisi;
    int i,j,temp,a;
    struct ogrInfo tablo[500];
    int say=0;
    while(ogrSay)
    {
        fscanf(oku,"%lld %s %s %s",&tablo[say].numara,&tablo[say].isim,&tablo[say].soyisim,&tablo[say].harf_not);
        say++;
        ogrSay--;
    }
    ogrSay=say;
	printf("��renci say�s� toplam :  %d\n\n",ogrSay);
	
	int sayac1=0;
	int sayac2=0;
	// harf notuna g�re her ��renci i�in 1 2  say�lar�n� atama
	for(i=0; i<ogrSay; i++)
	{
		if(!strcmp(tablo[i].harf_not, "AA")  || !strcmp(tablo[i].harf_not, "BA")  || !strcmp(tablo[i].harf_not, "BB") )
		{
			tablo[i].harfNotu = 1;
			sayac1++;
		}
		else if(!strcmp(tablo[i].harf_not, "CB")  || !strcmp(tablo[i].harf_not, "CC")  ||  !strcmp(tablo[i].harf_not, "DC")  || !strcmp(tablo[i].harf_not, "DD") )
		{
			tablo[i].harfNotu = 2;
			sayac2++;
		}
		else
		{
			continue;
		}	
	}
    fprintf(yaz1,"%15s %15s %15s %12s Not %12s Say�sal Not\n","Numara","�sim","Soyisim",ders.isim,ders.isim);
    fprintf(yaz2,"%15s %15s %15s %12s Not %12s Say�sal Not\n","Numara","�sim","Soyisim",ders.isim,ders.isim);
	for(i=0; i<ogrSay-1; i++)
	{
		printf("no: %-15lld  isim: %-15s  soyisim:  %-15s harfNotu: %-5s say�salNot: %-d\n",tablo[i].numara,tablo[i].isim,tablo[i].soyisim,tablo[i].harf_not,tablo[i].harfNotu);
		
		if(tablo[i].harfNotu == 1)
		{
            fprintf(yaz1,"%15lld %15s %15s %15s %5d\n",tablo[i].numara,tablo[i].isim,tablo[i].soyisim,tablo[i].harf_not,tablo[i].harfNotu);
		}
		else if(tablo[i].harfNotu == 2)
		{
            fprintf(yaz2,"%15lld %15s %15s %15s %5d\n",tablo[i].numara,tablo[i].isim,tablo[i].soyisim,tablo[i].harf_not,tablo[i].harfNotu);
		}
		else
		{
			continue;
		}	
	}
	printf("\n Harf notuna g�re gruplara ba�ar�yla b�l�nd�!\n\n");
}
//--------------------------------------------------------------------------------------------------------------------------
void NotBolme2(FILE *oku,int ogrSay,FILE *yaz1,FILE *yaz2,FILE *yaz3,struct dersInfo ders){
/*
	AA: 1	BA: 1	BB:1
	CB: 2	CC: 2	
	DC: 3	DD:3
*/
    int toplam=0,ortalama,sinifSayisi;
    int i,j,temp,a;
    struct ogrInfo tablo[500];
    int say=0;
// dosyadan listeyi okuma
    while(ogrSay)
    {
        fscanf(oku,"%lld %s %s %s",&tablo[say].numara,&tablo[say].isim,&tablo[say].soyisim,&tablo[say].harf_not);
        say++;
        ogrSay--;
    }
    ogrSay=say;
	printf("��renci say�s� toplam :  %d\n\n",ogrSay);
	int sayac1=0;
	int sayac2=0;
	int sayac3=0;
// harf notuna g�re her ��renci i�in 1 2 3 say�lar�n� atama
	for(i=0; i<ogrSay; i++)
	{
		if(!strcmp(tablo[i].harf_not, "AA")  || !strcmp(tablo[i].harf_not, "BA")  || !strcmp(tablo[i].harf_not, "BB") )
		{
			tablo[i].harfNotu = 1;
			sayac1++;
		}
		else if(!strcmp(tablo[i].harf_not, "CB")  || !strcmp(tablo[i].harf_not, "CC") )
		{
			tablo[i].harfNotu = 2;
			sayac2++;
		}
		else if(!strcmp(tablo[i].harf_not, "DC")  || !strcmp(tablo[i].harf_not, "DD") )
		{
			tablo[i].harfNotu = 3;
			sayac3++;
		}
		else
		{
			continue;
		}	
	}
// say�sal harf notuna g�re ��rencileri ayr� ayr� dosyalara yazma
	for(i=0; i<ogrSay-1; i++)
	{
		printf("no: %-15lld  isim: %-15s  soyisim:  %-15s harfNotu: %-5s say�salNot: %-d\n",tablo[i].numara,tablo[i].isim,tablo[i].soyisim,tablo[i].harf_not,tablo[i].harfNotu);
		
		if(tablo[i].harfNotu == 1)
		{
            fprintf(yaz1,"%15lld %15s %15s %15s %5d\n",tablo[i].numara,tablo[i].isim,tablo[i].soyisim,tablo[i].harf_not,tablo[i].harfNotu);
		}
		else if(tablo[i].harfNotu == 2)
		{
            fprintf(yaz2,"%15lld %15s %15s %15s %5d\n",tablo[i].numara,tablo[i].isim,tablo[i].soyisim,tablo[i].harf_not,tablo[i].harfNotu);
		}
		else if(tablo[i].harfNotu == 3)
		{
            fprintf(yaz3,"%15lld %15s %15s %15s %5d\n",tablo[i].numara,tablo[i].isim,tablo[i].soyisim,tablo[i].harf_not,tablo[i].harfNotu);
		}
		else
		{
			continue;
		}	
	}
	printf("\n Harf notuna g�re gruplara ba�ar�yla b�l�nd�!\n\n");
}
struct dersInfo *bilgiAlma(FILE *okuInfo, struct dersInfo *ders){
// ders_info dosyas�ndan bilgileri okuyup ders struct yap�s�na kaydetme
	fscanf(okuInfo,"%s\n",ders->isim);
	fscanf(okuInfo,"%s %s\n",ders->ogretmen_adi,ders->ogretmen_soyadi);
	fscanf(okuInfo,"%s\n",ders->ogretmen_mail);
	fgets(ders->dersZamani,100,okuInfo);
	
	return ders;
}
void bilgiVerme(struct dersInfo ders){
// dersle alakal� genel bilgileri ekrana basma
	printf("*******\n");
	printf("Dersin ad�: %s\n",ders.isim);
	printf("Dersin ��retmeninin ad�: %s %s\n",ders.ogretmen_adi,ders.ogretmen_soyadi);
	printf("Ders ��retmeninin mail adresi: %s\n",ders.ogretmen_mail);
	printf("%s\n",ders.dersZamani);
	printf("*******\n\n");
}
