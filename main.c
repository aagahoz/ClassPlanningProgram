#include "library.h"	// kendi k�t�phanemiz

int main(){

	int secim=1,ogrSay=0;
	struct dersInfo ders[3];	// ders struct� tan�m�
    FILE *oku,*yaz,*ekle,*yaz1,*yaz2,*yaz3,*okuInfo;	// dosya pointerlar�
	char INF212[40] = "INF212_liste.txt";	// temel dosya ad� inf212 i�in
	char MAT102[40] = "MAT102_liste.txt";	//
	char yeniDosya[40],sonDosya[40];	// dinamik dosya de�i�imi i�in
	int dosyasecimi=-1;  // ders dosyas� i�lemi se�imi i�in
	char infoDosya[15];	// dinamik ders dosyas� ad�n� tutmak i�in

	setlocale(LC_ALL, "Turkish");
	
	printf(" **  S�n�f Plan� Program�  ** \n\n");
	
	while(dosyasecimi){
		printf("��lem yap�lacak dersi se�iniz\n");
		printf("��kmak i�in 0\n");
		printf("%s dersi i�in 1\n","INF212");
		printf("%s dersi i�in 2\n >> ","MAT102");
		scanf("%d",&dosyasecimi);
		
	if(dosyasecimi == 0){
		printf("Program sonland�r�ld�!\n");
		system("Pause");
		return 0;
		}		
	else if(dosyasecimi == 1){
		strcpy(infoDosya,"INF212_info.txt");
	}
	else if(dosyasecimi == 2){
		strcpy(infoDosya,"MAT102_info.txt");
	}
	else if(dosyasecimi != 1 && dosyasecimi != 2 && dosyasecimi != 0){
		printf("Hatal� giri�, tekrar deneyin!\n");
		system("CLS");
		printf("\n");
		goto out;	// 0 1 2 d���nda de�er girilmesi durumunda en genel d�ng�n�n sonuna g�t�r�r ve duruma g�re tekrar sa�lan�r
	}
	if ((okuInfo = fopen(infoDosya,"r")) == NULL) {
	    printf("Error opening file!");
	    return 0;
	  	}

	bilgiAlma(okuInfo,&ders[dosyasecimi]);	// dersle alakal� genel bilgiler dosyadan al�n�r
	system("CLS");
	printf("\n");

	if(dosyasecimi == 1){	
		strcpy(sonDosya,INF212);
		printf("%s dersi i�in olu�acak dosya ad�n� giriniz (�rnek input: 'deneme.txt') >>  ",ders[dosyasecimi].isim);
		scanf("%s",&yeniDosya);
		printf("\n");
		if ((oku = fopen(sonDosya,"r")) == NULL) {
	        printf("Error opening file!");
	      	return 0;
	  			}
		if ((yaz = fopen(yeniDosya,"w")) == NULL) {
	      	printf("Error opening file!");
	      	return 0;
	  			}
		Duzeltme(oku,yaz,&ogrSay,ders[1]);	// belli ko�ullara g�re listenin ve dosyan�n yenilenmesi
		fclose(oku);
		fclose(yaz);
		strcpy(sonDosya,yeniDosya);		// program�n her yerinde kullan�labilmesi i�in d�zenlenmi� dosyan�n ad�n�n atamas�
		printf(">> Dosya D�zenlendi!  ->  Yeni dosyan�n  ad� < %s >\n\n",sonDosya);
	    secim = -1;

		while(secim)
		{
			printf("��renci say�s�: %d\n\n",ogrSay);
			
			printf("************************************************************************\n");		// i�lem sorusu
			printf("	0- Dersler sayfas�na ge�mek icin\n");
			printf("	1- Listeye yeni ��renci eklemek i�in\n");
			printf("	2- Listeden ��renci ��karmak i�in\n");
			printf("	3- Kullan�ma haz�r mevcut s�n�f say�s�na g�re liste olu�turmak i�in\n");
			printf("	4- Asistanlara g�re ��rencileri da��tmak i�in\n");
			printf("	5- INF211 dersini verme notuna g�re 2 gruba ay�rma i�in\n");
			printf("	6- INF211 dersini verme notuna g�re 3 gruba ay�rma i�in\n");
			printf("	7- %s dersi ile alakal� genel bilgileri almak i�in\n",ders[1].isim);
	
			printf("\n\n");
			printf("> Lutfen Yapmak Istediginiz Islemin Numarasini Giriniz >>  ");
			scanf("%d",&secim);			
	
			system("CLS");
			printf("\n");
			
			switch(secim){		// se�ilecek �a�r�lacak fonksiyon se�imi
			
			case(0):
				printf("\nDersler sayfas�na ge�ildi!\n");
				break;	
			
			case(1):
				if ((ekle=fopen(sonDosya,"a")) == NULL) {
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			ogrenciEkle(ekle,&ogrSay,ders[1]);		// listeye ve dosyaya yeni ��renci eklenmesi
				fclose(ekle);
				break;
					
			case(2):
				if ((yaz=fopen("new.txt","w")) == NULL) {
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			
				if ((oku=fopen(sonDosya,"r")) == NULL) {
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			ogrenciCikar(yaz,oku,&ogrSay,ders[1]);	//  varsa ��rencinin listeden ve dosyadan ��kar�lmas�
				fclose(oku);
				fclose(yaz);			
				break;
				
			case(3):
				if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatal� dosya olu�uyor
	      			printf("Error opening file!");
	      			return 0;
	  				}
	  				
	  			sinifOlusturma(oku,ogrSay,ders[1]);		// ��rencilerin s�n�f durumuna g�re b�l�nmesi ve dosyaya yaz�lmas�
				fclose(oku);
				break;
				
			case(4):
				if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatal� dosya olu�uyor
	      			printf("Error opening file!");
	      			return 0;
	  				}
	  			asistanBolme(oku,ogrSay,ders[1]);	// asistanlara g�re ��rencileri b�l�nmesi ve dosyaya yaz�lmas�
				fclose(oku);
				break;
				
			case(5):
				if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatal� dosya olu�uyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			if ((yaz1=fopen("1.grup.txt","w")) == NULL) {		// hatal� dosya olu�uyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			if ((yaz2=fopen("2.grup.txt","w")) == NULL) {		// hatal� dosya olu�uyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}

	  			NotBolme(oku,ogrSay,yaz1,yaz2,ders[1]);		// listenin 2 ye b�l�nmesi ve dosyaya yaz�lmas�
				fclose(oku);
				fclose(yaz1);
				fclose(yaz2);
				break;
				
			case(6):
				if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatal� dosya olu�uyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			if ((yaz1=fopen("1.grup.txt","w")) == NULL) {		// hatal� dosya olu�uyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			if ((yaz2=fopen("2.grup.txt","w")) == NULL) {		// hatal� dosya olu�uyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			if ((yaz3=fopen("3.grup.txt","w")) == NULL) {		// hatal� dosya olu�uyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			NotBolme2(oku,ogrSay,yaz1,yaz2,yaz3,ders[1]); // notlara g�re 3 e b�l�nmesi ve dosyaya yaz�lmas�
				fclose(oku);
				fclose(yaz1);
				fclose(yaz2);
				fclose(yaz3);
				break;
				
			case(7):	
		    	bilgiVerme(ders[1]);
		    	break;
			default:
				printf(">> Ge�ersiz ��lem Kodu, Tekrar Deneyiniz!\n\n");
				break;
			}
		}
	}
		else if(dosyasecimi == 2){
			strcpy(sonDosya,INF212);
        	printf("%s dersi i�in olu�acak dosya ad�n� giriniz (�rnek input: 'deneme.txt') >>  ",ders[dosyasecimi].isim);	// d�zenlenmi� listenin  ad�n�n belirlenmesi
	        scanf("%s",&yeniDosya);
	        printf("\n");
	        if ((oku = fopen(sonDosya,"r")) == NULL) {
            	printf("Error opening file!");
      	    	return 0;
  			}
	        if ((yaz = fopen(yeniDosya,"w")) == NULL) {
      	    	printf("Error opening file!");
      	    	return 0;
  			}
		    Duzeltme(oku,yaz,&ogrSay,ders[2]);	//listenin belli bir d�zene g�re yenilenmesi
		    fclose(oku);
		    fclose(yaz);
		    strcpy(sonDosya,yeniDosya);	 	// d�zenlenmi� dosyan�n t�m programda kullan�lmas� i�in
	        printf(">> Dosya D�zenlendi!  ->  Yeni dosyan�n  ad� < %s >\n\n",sonDosya);
      	    secim = -1;

	    	while(secim){
			    printf("��renci say�s�: %d\n\n",ogrSay);
			
			    printf("************************************************************************\n");		// i�lem sorusu
			    printf("	0- Dersler sayfas�na ge�mek i�in icin\n");
			    printf("	1- Listeye yeni ��renci eklemek i�in\n");
			    printf("	2- Listeden ��renci ��karmak i�in\n");
			    printf("	3- Kullan�ma haz�r mevcut s�n�f say�s�na g�re liste olu�turmak i�in\n");
			    printf("	4- Asistanlara g�re ��rencileri da��tmak i�in\n");
				printf("	5- MAT101 dersini verme notuna g�re 2 gruba ay�rma i�in\n");
				printf("	6- MAT101 dersini verme notuna g�re 3 gruba ay�rma i�in\n");
				printf("	7- %s dersi ile alakal� genel bilgileri almak i�in\n",ders[2].isim);
			    printf("\n\n");
			    printf("> Lutfen Yapmak Istediginiz Islemin Numarasini Giriniz >>  ");
			    scanf("%d",&secim);			
	
			    system("CLS");
		     	printf("\n");
			
		    	switch(secim){		// se�ilecek �a�r�lacak fonksiyon se�imi
			
			    case(0):
			    	printf("\nDersler sayfas�na ge�ildi!\n");
			    	break;	
			
			    case(1):
				    if ((ekle=fopen(sonDosya,"a")) == NULL) {
	      		    	printf("Error opening file!");
	      				return 0;
	  				}
	  				ogrenciEkle(ekle,&ogrSay,ders[2]);		// listeye yeni ��renci eklenmesi ve ilgili dosyaya yaz�mas�
					fclose(ekle);
					break;
				
			    case(2):
				    if ((yaz=fopen("new.txt","w")) == NULL) {
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
	  				
				    if ((oku=fopen(sonDosya,"r")) == NULL) {
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
	  				ogrenciCikar(yaz,oku,&ogrSay,ders[2]);  // ��rencinin listeden bulunmas� durumunda listeden ve dosyadan ��kar�lmas�
					fclose(oku);
					fclose(yaz);			
					break;
				
			    case(3):
				    if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatal� dosya olu�uyor
	      				printf("Error opening file!");
	      				return 0;
	  					}
	  				sinifOlusturma(oku,ogrSay,ders[2]);		// belirlenen durumlara g�re s�n�flar�n olu�turulmas� ve dosyaya yaz�lmas�
					fclose(oku);
					break;
				
			    case(4):
				    if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatal� dosya olu�uyor
	      				printf("Error opening file!");
	      				return 0;
	  					}
	  				asistanBolme(oku,ogrSay,ders[2]);		// asistanlara ��renciler b�l�nmesi ve dosyaya yaz�lmas�
					fclose(oku);
					break;
				
		    	case(5):
				    if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatal� dosya olu�uyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
	  		    	if ((yaz1=fopen("1.grup.txt","w")) == NULL) {		// hatal� dosya olu�uyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
	  			    if ((yaz2=fopen("2.grup.txt","w")) == NULL) {		// hatal� dosya olu�uyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
		
		  			NotBolme(oku,ogrSay,yaz1,yaz2,ders[2]);	// notlara g�re 2 ye b�lme ve dosyaya yaz�lmas�
					fclose(oku);
					fclose(yaz1);
					fclose(yaz2);
					break;
					
			    case(6):
				    if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatal� dosya olu�uyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
	  		        if ((yaz1=fopen("1.grup.txt","w")) == NULL) {		// hatal� dosya olu�uyor
	      		    	printf("Error opening file!");
	      		 	 	return 0;
	  					}
	  		    	if ((yaz2=fopen("2.grup.txt","w")) == NULL) {		// hatal� dosya olu�uyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
	  		    	if ((yaz3=fopen("3.grup.txt","w")) == NULL) {		// hatal� dosya olu�uyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
		  		    NotBolme2(oku,ogrSay,yaz1,yaz2,yaz3,ders[2]);	// notlara g�re 3 e b�lme ve dosyaya yaz�lmas�
					fclose(oku);
				    fclose(yaz1);
			    	fclose(yaz2);
				    fclose(yaz3);
				    break;
				    	
			    case(7):
			    	bilgiVerme(ders[2]); // dersle alakal� genel bilgiler ekrana basma
			    	break;
		     	default:
					printf(">> Ge�ersiz ��lem Kodu, Tekrar Deneyiniz!\n\n");
					break;
				}
		  	}
		}
		out:
			printf("Hatal� Giri�, Yeniden Deneyin!\n");
	}
	printf("\n\n");
	system("PAUSE");
    return 0;
}
