#include "library.h"	// kendi kütüphanemiz

int main(){

	int secim=1,ogrSay=0;
	struct dersInfo ders[3];	// ders structý tanýmý
    FILE *oku,*yaz,*ekle,*yaz1,*yaz2,*yaz3,*okuInfo;	// dosya pointerlarý
	char INF212[40] = "INF212_liste.txt";	// temel dosya adý inf212 için
	char MAT102[40] = "MAT102_liste.txt";	//
	char yeniDosya[40],sonDosya[40];	// dinamik dosya deðiþimi için
	int dosyasecimi=-1;  // ders dosyasý iþlemi seçimi için
	char infoDosya[15];	// dinamik ders dosyasý adýný tutmak için

	setlocale(LC_ALL, "Turkish");
	
	printf(" **  Sýnýf Planý Programý  ** \n\n");
	
	while(dosyasecimi){
		printf("Ýþlem yapýlacak dersi seçiniz\n");
		printf("Çýkmak için 0\n");
		printf("%s dersi için 1\n","INF212");
		printf("%s dersi için 2\n >> ","MAT102");
		scanf("%d",&dosyasecimi);
		
	if(dosyasecimi == 0){
		printf("Program sonlandýrýldý!\n");
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
		printf("Hatalý giriþ, tekrar deneyin!\n");
		system("CLS");
		printf("\n");
		goto out;	// 0 1 2 dýþýnda deðer girilmesi durumunda en genel döngünün sonuna götürür ve duruma göre tekrar saðlanýr
	}
	if ((okuInfo = fopen(infoDosya,"r")) == NULL) {
	    printf("Error opening file!");
	    return 0;
	  	}

	bilgiAlma(okuInfo,&ders[dosyasecimi]);	// dersle alakalý genel bilgiler dosyadan alýnýr
	system("CLS");
	printf("\n");

	if(dosyasecimi == 1){	
		strcpy(sonDosya,INF212);
		printf("%s dersi için oluþacak dosya adýný giriniz (örnek input: 'deneme.txt') >>  ",ders[dosyasecimi].isim);
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
		Duzeltme(oku,yaz,&ogrSay,ders[1]);	// belli koþullara göre listenin ve dosyanýn yenilenmesi
		fclose(oku);
		fclose(yaz);
		strcpy(sonDosya,yeniDosya);		// programýn her yerinde kullanýlabilmesi için düzenlenmiþ dosyanýn adýnýn atamasý
		printf(">> Dosya Düzenlendi!  ->  Yeni dosyanýn  adý < %s >\n\n",sonDosya);
	    secim = -1;

		while(secim)
		{
			printf("Öðrenci sayýsý: %d\n\n",ogrSay);
			
			printf("************************************************************************\n");		// iþlem sorusu
			printf("	0- Dersler sayfasýna geçmek icin\n");
			printf("	1- Listeye yeni öðrenci eklemek için\n");
			printf("	2- Listeden öðrenci çýkarmak için\n");
			printf("	3- Kullanýma hazýr mevcut sýnýf sayýsýna göre liste oluþturmak için\n");
			printf("	4- Asistanlara göre öðrencileri daðýtmak için\n");
			printf("	5- INF211 dersini verme notuna göre 2 gruba ayýrma için\n");
			printf("	6- INF211 dersini verme notuna göre 3 gruba ayýrma için\n");
			printf("	7- %s dersi ile alakalý genel bilgileri almak için\n",ders[1].isim);
	
			printf("\n\n");
			printf("> Lutfen Yapmak Istediginiz Islemin Numarasini Giriniz >>  ");
			scanf("%d",&secim);			
	
			system("CLS");
			printf("\n");
			
			switch(secim){		// seçilecek çaðrýlacak fonksiyon seçimi
			
			case(0):
				printf("\nDersler sayfasýna geçildi!\n");
				break;	
			
			case(1):
				if ((ekle=fopen(sonDosya,"a")) == NULL) {
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			ogrenciEkle(ekle,&ogrSay,ders[1]);		// listeye ve dosyaya yeni öðrenci eklenmesi
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
	  			ogrenciCikar(yaz,oku,&ogrSay,ders[1]);	//  varsa öðrencinin listeden ve dosyadan çýkarýlmasý
				fclose(oku);
				fclose(yaz);			
				break;
				
			case(3):
				if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatalý dosya oluþuyor
	      			printf("Error opening file!");
	      			return 0;
	  				}
	  				
	  			sinifOlusturma(oku,ogrSay,ders[1]);		// öðrencilerin sýnýf durumuna göre bölünmesi ve dosyaya yazýlmasý
				fclose(oku);
				break;
				
			case(4):
				if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatalý dosya oluþuyor
	      			printf("Error opening file!");
	      			return 0;
	  				}
	  			asistanBolme(oku,ogrSay,ders[1]);	// asistanlara göre öðrencileri bölünmesi ve dosyaya yazýlmasý
				fclose(oku);
				break;
				
			case(5):
				if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatalý dosya oluþuyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			if ((yaz1=fopen("1.grup.txt","w")) == NULL) {		// hatalý dosya oluþuyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			if ((yaz2=fopen("2.grup.txt","w")) == NULL) {		// hatalý dosya oluþuyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}

	  			NotBolme(oku,ogrSay,yaz1,yaz2,ders[1]);		// listenin 2 ye bölünmesi ve dosyaya yazýlmasý
				fclose(oku);
				fclose(yaz1);
				fclose(yaz2);
				break;
				
			case(6):
				if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatalý dosya oluþuyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			if ((yaz1=fopen("1.grup.txt","w")) == NULL) {		// hatalý dosya oluþuyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			if ((yaz2=fopen("2.grup.txt","w")) == NULL) {		// hatalý dosya oluþuyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			if ((yaz3=fopen("3.grup.txt","w")) == NULL) {		// hatalý dosya oluþuyor
	      		    printf("Error opening file!");
	      			return 0;
	  				}
	  			NotBolme2(oku,ogrSay,yaz1,yaz2,yaz3,ders[1]); // notlara göre 3 e bölünmesi ve dosyaya yazýlmasý
				fclose(oku);
				fclose(yaz1);
				fclose(yaz2);
				fclose(yaz3);
				break;
				
			case(7):	
		    	bilgiVerme(ders[1]);
		    	break;
			default:
				printf(">> Geçersiz Ýþlem Kodu, Tekrar Deneyiniz!\n\n");
				break;
			}
		}
	}
		else if(dosyasecimi == 2){
			strcpy(sonDosya,INF212);
        	printf("%s dersi için oluþacak dosya adýný giriniz (örnek input: 'deneme.txt') >>  ",ders[dosyasecimi].isim);	// düzenlenmiþ listenin  adýnýn belirlenmesi
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
		    Duzeltme(oku,yaz,&ogrSay,ders[2]);	//listenin belli bir düzene göre yenilenmesi
		    fclose(oku);
		    fclose(yaz);
		    strcpy(sonDosya,yeniDosya);	 	// düzenlenmiþ dosyanýn tüm programda kullanýlmasý için
	        printf(">> Dosya Düzenlendi!  ->  Yeni dosyanýn  adý < %s >\n\n",sonDosya);
      	    secim = -1;

	    	while(secim){
			    printf("Öðrenci sayýsý: %d\n\n",ogrSay);
			
			    printf("************************************************************************\n");		// iþlem sorusu
			    printf("	0- Dersler sayfasýna geçmek için icin\n");
			    printf("	1- Listeye yeni öðrenci eklemek için\n");
			    printf("	2- Listeden öðrenci çýkarmak için\n");
			    printf("	3- Kullanýma hazýr mevcut sýnýf sayýsýna göre liste oluþturmak için\n");
			    printf("	4- Asistanlara göre öðrencileri daðýtmak için\n");
				printf("	5- MAT101 dersini verme notuna göre 2 gruba ayýrma için\n");
				printf("	6- MAT101 dersini verme notuna göre 3 gruba ayýrma için\n");
				printf("	7- %s dersi ile alakalý genel bilgileri almak için\n",ders[2].isim);
			    printf("\n\n");
			    printf("> Lutfen Yapmak Istediginiz Islemin Numarasini Giriniz >>  ");
			    scanf("%d",&secim);			
	
			    system("CLS");
		     	printf("\n");
			
		    	switch(secim){		// seçilecek çaðrýlacak fonksiyon seçimi
			
			    case(0):
			    	printf("\nDersler sayfasýna geçildi!\n");
			    	break;	
			
			    case(1):
				    if ((ekle=fopen(sonDosya,"a")) == NULL) {
	      		    	printf("Error opening file!");
	      				return 0;
	  				}
	  				ogrenciEkle(ekle,&ogrSay,ders[2]);		// listeye yeni öðrenci eklenmesi ve ilgili dosyaya yazýmasý
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
	  				ogrenciCikar(yaz,oku,&ogrSay,ders[2]);  // öðrencinin listeden bulunmasý durumunda listeden ve dosyadan çýkarýlmasý
					fclose(oku);
					fclose(yaz);			
					break;
				
			    case(3):
				    if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatalý dosya oluþuyor
	      				printf("Error opening file!");
	      				return 0;
	  					}
	  				sinifOlusturma(oku,ogrSay,ders[2]);		// belirlenen durumlara göre sýnýflarýn oluþturulmasý ve dosyaya yazýlmasý
					fclose(oku);
					break;
				
			    case(4):
				    if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatalý dosya oluþuyor
	      				printf("Error opening file!");
	      				return 0;
	  					}
	  				asistanBolme(oku,ogrSay,ders[2]);		// asistanlara öðrenciler bölünmesi ve dosyaya yazýlmasý
					fclose(oku);
					break;
				
		    	case(5):
				    if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatalý dosya oluþuyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
	  		    	if ((yaz1=fopen("1.grup.txt","w")) == NULL) {		// hatalý dosya oluþuyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
	  			    if ((yaz2=fopen("2.grup.txt","w")) == NULL) {		// hatalý dosya oluþuyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
		
		  			NotBolme(oku,ogrSay,yaz1,yaz2,ders[2]);	// notlara göre 2 ye bölme ve dosyaya yazýlmasý
					fclose(oku);
					fclose(yaz1);
					fclose(yaz2);
					break;
					
			    case(6):
				    if ((oku=fopen(sonDosya,"r")) == NULL) {		// hatalý dosya oluþuyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
	  		        if ((yaz1=fopen("1.grup.txt","w")) == NULL) {		// hatalý dosya oluþuyor
	      		    	printf("Error opening file!");
	      		 	 	return 0;
	  					}
	  		    	if ((yaz2=fopen("2.grup.txt","w")) == NULL) {		// hatalý dosya oluþuyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
	  		    	if ((yaz3=fopen("3.grup.txt","w")) == NULL) {		// hatalý dosya oluþuyor
	      		    	printf("Error opening file!");
	      				return 0;
	  					}
		  		    NotBolme2(oku,ogrSay,yaz1,yaz2,yaz3,ders[2]);	// notlara göre 3 e bölme ve dosyaya yazýlmasý
					fclose(oku);
				    fclose(yaz1);
			    	fclose(yaz2);
				    fclose(yaz3);
				    break;
				    	
			    case(7):
			    	bilgiVerme(ders[2]); // dersle alakalý genel bilgiler ekrana basma
			    	break;
		     	default:
					printf(">> Geçersiz Ýþlem Kodu, Tekrar Deneyiniz!\n\n");
					break;
				}
		  	}
		}
		out:
			printf("Hatalý Giriþ, Yeniden Deneyin!\n");
	}
	printf("\n\n");
	system("PAUSE");
    return 0;
}
