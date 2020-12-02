/*
 * *********************************
 **** PİZZA ADMIN SİSTEMİ ****     *
 * ***************************     *               		   
 * Yusuf Özkan *
 */
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <unistd.h>

int a=0; //pizzalar dizisinin boyutu için global değişken.

typedef struct musteri   //müşterilerin bilgilerini barındıran müşteri struct'ı
{
	char id[10];// müşteri id'si ...
	char isim[20];
	char soyisim[20];
	char telno[20];
	char adres[100];
	
} Musteri; 

Musteri m;  //musteri struct'ı tipinde değişken

typedef struct siparis
{
	char id[20];// siparis id'si
	char mid[20];// müşteri id'si
	int pid;// pizzanın id'si
	char fiyat[10];// pizzanın fiyatı
	char tarih[15];
	
} Siparis;

Siparis s; //siparis struct'ı tipinde değişken

char *pizzalar[100] = 
	{"vejeteryan,ince,kucuk","vejeteryan,ince,orta","vejeteryan,ince,buyuk",
	"vejeteryan,kalin,kucuk","vejeteryan,kalin,orta","vejeteryan,kalin,buyuk",
	"margarita,ince,kucuk","margarita,ince,orta","margarita,ince,buyuk",
	"margarita,kalin,kucuk","margarita,kalin,orta","margarita,kalin,buyuk",
	"mexico,ince,kucuk","mexico,ince,orta","mexico,ince,buyuk",
	"mexico,kalin,kucuk","mexico,kalin,orta","mexico,kalin,buyuk"};
	
	// pizzalar pointer dizisinde tutuldu ekleme yapılırsa dizi ona göre
	// 100 pizzaya kadar esneyebilir.
	
float fiyatlar[100] = {15.99,18.99,19.99,18.99,19.99,20.99,16.99,17.99,20.99,
				  17.99,19.99,21.99,17.99,18.99,20.99,15.99,17.99,27.99};

// fiyatları da tek boyutlu dizide tutuldu


void pizza_yazdir(char *pizzalar[], float fiyatlar[])
{
	printf("\nPizzalar:\n");
	for(int i = 0; i < a; i++) //pizza ID 'si,adı ve fiyatını ekrana yazdırır
	{
		printf("%d - %s = ",i+1,pizzalar[i]);
		printf("%.2f $\n", fiyatlar[i]);
	}
	
}

void pizza_txtyazdir(char *pizzalar[],float fiyatlar[])
{
	FILE *file2 = fopen("pizza.txt","w"); // pizza.txt yoksa oluşturur ve en baştan yazmaya başlamak üzere açar.


	for(int i = 0; i < a; i++) //dizi boyutuna göre döner ve txt'ye pizzaları geçirir.
	{
		fprintf(file2,"%d - %s = %.2f $\n",i+1,pizzalar[i],fiyatlar[i]);
	}
	
}

void musteri_yazdir()
{
	char l[150];
	FILE *file3 = fopen("musteri.txt","r"); // musteri.txt var ise onu okur .
	printf("\nKayitli Musteriler:");
	printf("\nID\tISIM\tSOYISIM\tNUMARA\t\tADRES\n");
	
	
	while(fgets(l,150,file3) != NULL)  //l dizisinde geçirir ve onu yazdırır.
	{
		printf("%s",l);
	}


}

void musteriekle(struct musteri Musteri)
{
	FILE* file3 = fopen("musteri.txt", "a"); //musteri.txt'ye kayıtlı müşterilerin devamı olacak nitelikte müşteri ekler.

	printf("\nMusteri Ekle");
	printf("\nID: ");
	scanf("%s",m.id);
	printf("Isim: ");
	scanf("%s",m.isim);
	printf("Soyisim: ");
	scanf("%s",m.soyisim);
	printf("Telefon: ");
	scanf("%s",m.telno);
	printf("Adres: ");
	scanf("%s,",m.adres);
	
	fprintf(file3,"%s\t%s\t%s\t%s\t%s\n",m.id,m.isim,m.soyisim,m.telno,m.adres); //txt'ye geçirir.


}

void musteri_sil() //txt'deki müşteri bilgilerini IDsine göre satır olarak siler.
{
	char temp1[150]; // geçici 2 dizi tanımlandı.
	char temp2[150];
	
	char id[20];
	printf("\nSilinecek musterinin ID'si: ");
	scanf("%s",id); //karşılaştırılıcak ID alındı.
			

	FILE* f = fopen("musteri.txt", "r+"); //musteri txt okunmak ve yazmak için açıldı
	FILE* temp = fopen("temp.txt", "w");  // geçici bir file açıldı

	while (fgets(temp1, 150, f) != NULL) //f'ten 150 karakter okur
	{
		
		memcpy(temp2, temp1, 150); //byte kopyalama işlemi.

		char* tmp = strtok(temp1, "\t"); //temp1 dizisinden ilk taba kadar olan kısmı pointerda tutar

		if (!strcmp(tmp,id)) 
		{
			continue;  //idler uyuşursa onu atla ve yazma,devam et.
		}                                     
		else 
		{
			fprintf(temp, "%s", temp2);//temp2 geçici dizisinden temp dosyasına diğer kullanıcıları yaz.
		}
	}
	fclose(f);  //dosyaları kapatır.
	fclose(temp);
	

	f = fopen("musteri.txt", "w");//musteri txt'yi yazmak üzere açar
	temp = fopen("temp.txt", "r+"); // geçici dosyayı okumak ve yazmak üzere açar.

	while (fgets(temp1, 150, temp) != NULL) // dosyadan diziye 150 karakter oku.
	{
		memcpy(temp2, temp1, 150); //byte kopyalama işlemi.
		fprintf(f, "%s", temp2);  // geçici diziden asıl dosyaya silinmiş şekilde aktarma yapılır
	}
	fclose(f); //dosyalar kapanır.
	fclose(temp);
}

void musteri_guncelle(struct musteri Musteri)
{
	char temp1[150]; // geçici diziler tanımlandı.
	char temp2[150];
	
	char id[20];
	printf("\nMusteri guncelle");
	printf("\nGuncellenecek musterinin ID'si: ");  
	scanf("%s",id);  // güncellenecek ID.
			

	FILE* f = fopen("musteri.txt", "r+"); // müşteri dosyası okumak ve yazmak için açıldı
	FILE* temp = fopen("temp.txt", "w");  // geçici dosya bir yazmak üzere açıldı 

	while (fgets(temp1, 150, f) != NULL)  // müşterilerden 150 karakter diziye aktar
	{
		
		memcpy(temp2, temp1, 150); // temp1'i 2ye kopyalar

		char* tmp = strtok(temp1, "\t"); // ID kısmını pointerda tutup karşılaştırır
		
		fclose(temp); // yazma işlemi bittiğinden dolayı geçici dosya kapatıldı.
		
		if (!strcmp(tmp,id)) //ID'ler uyuşursa geçici dosyaya yeni bilgileri al
		{
			FILE* file3 = fopen("temp.txt", "a"); // geçici dosya devamına yazmak üzere açıldı

			printf("\nMusteri guncelle");
			printf("Isim: ");
			scanf("%s",m.isim);
			printf("Soyisim: ");
			scanf("%s",m.soyisim);
			printf("Telefon: ");
			scanf("%s",m.telno);
			printf("Adres: ");
			scanf("%s,",m.adres);
	
			fprintf(file3,"%s\t%s\t%s\t%s\t%s\n",id,m.isim,m.soyisim,m.telno,m.adres);
		
			fclose(file3); //yazılıp kapatıldı
		}                                     
		else 
		{
			FILE* temp = fopen("temp.txt", "a");
			fprintf(temp, "%s", temp2);  //geçici diziden geçici dosyaya aktarma yapıldı
		}
	}
	fclose(f);
	fclose(temp); // dosyalaar kapatıldı.

	
	f = fopen("musteri.txt", "w"); //üzerine silip yazılmak üzere açıldı.
	temp = fopen("temp.txt", "r+"); // okuyup yazılmak üzere açıldı.
	// FILE diye yukarıda belirtildiğinden tekrar belirtme yapılmadı..
	

	while (fgets(temp1, 150, temp) != NULL)// geçici dosyadan diziye 150 karakter okundu.
	{
		memcpy(temp2, temp1, 150); //byte kopyalama işlemi.
		fprintf(f, "%s", temp2); //diziden asıl dosyaya güncellenmiş bilgiler yazıldı.
	}
	
	fclose(f); // dosyalar kapatıldı.
	fclose(temp);
		
}


void pizza_ekle(char *pizzalar[], float fiyatlar[])
{	
	printf("\nPizza Ekle");

	int i = 1; // ekleme işlemine devam edilip edilmeyeceğini kontrol için kullanılacak
	
	while(i!=0) // kullanıcı 0'a basana kadar döner.
	{
		pizzalar[a] = (char*)malloc(50);//pizzalar dizisi için hafızadan 50 charlık yer ayırıldı.
		
		printf("\nPizza ismi,Kenar,Boyut olarak virgulle ayirarak giriniz: ");
		scanf("%s",pizzalar[a]); // girilen değer diziye eklenir.

		a++;// eğer buraya girerese pizzalar artmış olacak ve yazdırırken kullanılan a değişkeni artırılması gerekecek.
		
		printf("\nFiyatini giriniz:");
		scanf("%f",&fiyatlar[a]); // grilen değer fiyatlara eklenir ve aynı pizzanın karşısına denk gelir.
		
		printf("Devam etmek icin 1,cikmak icin 0'a basin.");
		scanf("%d",&i); // döngüden çıkma kontrolü.
		
	}
	
}


void pizza_fiyat_guncelle(float fiyatlar[])
{
	int id;
	float yenifiyat;  
	
	printf("\nFiyat guncellemek istediginiz pizzanin ID'sini giriniz :");
	scanf("%d",&id);
	printf("\nSu anki fiyat: %.2f",fiyatlar[id-1]); // şu an bulunan id'deki fiyatı gösterir

	printf("\n\nYeni fiyatini giriniz :");
	scanf("%f",&yenifiyat);
	
	fiyatlar[id-1]=yenifiyat;  // yeni girilen fiyatı günceller
	printf("\nYeni fiyat: %.2f",fiyatlar[id-1]); // ve gösterir
	
}

void pizza_sil(char *pizzalar[],float fiyatlar[]) // pizzayı dizide silindi olarak gösterir ve fiyatta 0.00 yazar.
{
	int id;
	printf("Silinecek pizzanin ID'si :");
	scanf("%d",&id); 
	
	pizzalar[id-1]="--------Silindi----------";
	fiyatlar[id-1]=0.0000000;
	
}


void siparis_al(struct siparis Siparis, float fiyatlar[])
{
	FILE *file1 =  fopen("siparis.txt","a");// siparis txt üzerine yazılmak üzere açılır.
	
	printf("\nSiparis ID: ");// siparis IDsi
	scanf("%s",s.id);                 
	printf("Musterinin ID'si: ");
	scanf("%s",s.mid);
	printf("Tarih: ");       // değerler alınıp değişkene atanır
	scanf("%s",s.tarih);
	printf("Pizzanin ID'si: ");
	scanf("%d",&s.pid);
	
	// tek tek dosyaya yazılır.
	fprintf(file1,"%s\t%s\t%.2f\t%s\n",s.id,s.mid,fiyatlar[s.pid-1],s.tarih);
}

int main()
{
	int secim;
	
	pizza_txtyazdir(pizzalar,fiyatlar); // pizza.txt'yi oluşturur ve pizzaları içine yazar
	
	printf("---------PIZZA MEDENIYET ADMIN SISTEMINE HOSGELDINIZ---------\n\n\n");
	
	label:  // ana menüye dönmek için etiket tanımlandı.
	
	a=0;
	
	while(pizzalar[a]!=NULL)
	{
		a++;
	}
	
	printf("\n\n1.MUSTERI EKLE\n");
	printf("2.MUSTERI SIL\n");
	printf("3.MUSTERI BILGILERI GUNCELLE\n");
	printf("4.PIZZA EKLE\n");
	printf("5.PIZZA FIYAT GUNCELLE\n");
	printf("6.PIZZA SIL\n");
	printf("7.SIPARIS AL\n");
	printf("0.AYRIL\n");
	printf("\nYUKARIDAKI ISLEMLERDEN BIRINI SECINIZ:");
	scanf("%d",&secim);
	printf("\n");
	
	switch(secim) // basılan tuşa göre işlemleri yapar.
	{
		case 1:
			musteriekle(m);
			break;
		case 2:
			musteri_yazdir();
			
			musteri_sil();
			break;
		case 3:
			musteri_yazdir();
			musteri_guncelle(m);
			break;
		case 4:
			pizza_ekle(pizzalar,fiyatlar);
			pizza_txtyazdir(pizzalar,fiyatlar);
			
			break;
		case 5:
			pizza_yazdir(pizzalar,fiyatlar);
			pizza_fiyat_guncelle(fiyatlar);
			pizza_yazdir(pizzalar,fiyatlar);
			pizza_txtyazdir(pizzalar,fiyatlar);
			break;
		case 6:
			pizza_yazdir(pizzalar,fiyatlar);
			pizza_sil(pizzalar,fiyatlar);
			pizza_txtyazdir(pizzalar,fiyatlar);
			break;
		case 7:
			pizza_yazdir(pizzalar,fiyatlar);
			musteri_yazdir();
			siparis_al(s,fiyatlar);
			break;
		case 0:
			printf("Sistemden çikiliyor...");
			sleep(3);          // Sistemden 3 saniye içinde çıkar
			
			return 0;
		default:
			printf("Gecersiz islem!\n");
			return 0;
	}
	
	goto label;  // etiket ile ana sayfaya dönüş sağlandı.
	
	return 58;
}
