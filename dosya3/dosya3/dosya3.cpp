#include<iostream>
#include<Windows.h>

// kaynak video:https://www.youtube.com/watch?v=Au4C3nU4HqI&list=PLIM5iw4GHbNU2gOPQ4pcqkHZuyQdRazc9&index=3
using namespace std;

enum YON {  //sabit değerler belirliyoruz

	YON_SOL = 1,
	YON_SAG = 2,
	YON_YUKARI = 3,
	YON_ASAGI = 4

};

// her bir yılan hücresinin kullanacağı veri yapısı tasarlayalım
struct YilanHucre
{
	int x;  //koordinatları
	int y;

	YON yon;
	char karakter;
};

const int genislik = 80; // sabit bir değişken oluşturduk.Nereye kadar gideceğini belirttik
const int yukseklik = 20;
const int maxYilanUzunlugu = 500;
const char yilanKarakteri = 219;
int kuyrukUzunlugu = 0;
char sahne[genislik][yukseklik];
char tuslar[256]; //bütün tuşlarla ilgili bilgiyi dizi içerisinde tutuyoruz.


//yılan uzunluğuğ için dizi
YilanHucre yilanKuyrugu[maxYilanUzunlugu];



//Windows'a özgü fonksiyondan yararlanarak klavye verilerine göre hareket etmesini sağlayacağız.
void klavyeOku(char tuslar[])
{
	for (int x = 0; x < 256; x++)
		tuslar[x] = (char)(GetAsyncKeyState(x) >> 8); //asenkron çalışıyor



}


//Konum belirtek,koordinatı değiştirmek için windows apı'den yararlanıyoruz.Bunun için fonksiyonu tanımlayalım

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void kursoruGizle()
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO  cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = false; //görünürlüğü false yaptık
	SetConsoleCursorInfo(out, &cursorInfo);
}

void sahneyiCiz()
{
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			cout << sahne[x][y];
		}
		cout << endl;
	}


}
void sahneyiTemizle()
{
	for (int y = 0; y < yukseklik; y++)
	{
		for (int x = 0; x < genislik; x++)
		{
			sahne[x][y] = ' ';
		}

	}


}

void sinirlariolustur()
{
	for (int x = 0; x < genislik; x++)
	{
		sahne[x][0] = 219;
		sahne[x][yukseklik - 1] = 219;
	}

	for (int y = 0; y < yukseklik; y++)
	{
		sahne[0][y] = 219;
		sahne[genislik - 1][y] = 219;

	}
}

void yilaniHareketEttir()
{

	for (int i = 0; i < kuyrukUzunlugu; i++)
	{
		switch (yilanKuyrugu[i].yon)
		{
		case YON_SAG:
			yilanKuyrugu[i].x++;
			break;
		case YON_SOL:
			yilanKuyrugu[i].x--;
			break;
		case YON_ASAGI:
			yilanKuyrugu[i].y++;
			break;
		case YON_YUKARI:
			yilanKuyrugu[i].y--;
			break;

		}

		
	}
	for (int i= kuyrukUzunlugu- 1; i>0; i--)
	{
		yilanKuyrugu[i].yon = yilanKuyrugu[i-1].yon;
	}


}
void yilanKuyrugunaEkle()
{

	if (kuyrukUzunlugu == maxYilanUzunlugu)
		return;


	int x = yilanKuyrugu[kuyrukUzunlugu - 1].x;
	int y = yilanKuyrugu[kuyrukUzunlugu - 1].y;
	YON yon = yilanKuyrugu[kuyrukUzunlugu - 1].yon;
	char kar = yilanKuyrugu[kuyrukUzunlugu - 1].karakter;

	switch (yilanKuyrugu[kuyrukUzunlugu - 1].yon)
	{
	case YON_SAG:
		x--;
		break;
	case YON_SOL:
		x++;
		break;
	case YON_ASAGI:
		y--;
		break;
	case YON_YUKARI:
		y++;
		break;

	}

	yilanKuyrugu[kuyrukUzunlugu].x = x;
	yilanKuyrugu[kuyrukUzunlugu].y = y;
	yilanKuyrugu[kuyrukUzunlugu].yon = yon;
	yilanKuyrugu[kuyrukUzunlugu].karakter = kar;

	kuyrukUzunlugu++;

}

void yilanOlustur()
{
	kuyrukUzunlugu = 1;
	
	//yılanın ilk elemanına koordinat atıyoruz.
	yilanKuyrugu[0].x = 20;
	yilanKuyrugu[0].y = 10;
	yilanKuyrugu[0].yon = YON_SAG;
	yilanKuyrugu[0].karakter = yilanKarakteri;
	yilanKuyrugunaEkle();
	yilanKuyrugunaEkle();
}

void yilaniSahneyeYerlestir()
{
	for (int i = 0; i < kuyrukUzunlugu; i++)
	{
		int x = yilanKuyrugu[i].x;
		int y = yilanKuyrugu[i].y;
		sahne[x][y] = yilanKuyrugu[i].karakter;
	}

}

void klavyeKontrol()
{
	klavyeOku(tuslar);
	if (tuslar['A'] != 0) //harfe basınca sola gitmesi için
	{
		yilanKuyrugu[0].yon = YON_SOL;
	}

	if (tuslar['D'] != 0) //harfe basınca sağa gitmesi için
	{
		yilanKuyrugu[0].yon = YON_SAG;
	}

	if (tuslar['W'] != 0) //harfe basınca yukarı gitmesi için
	{
		yilanKuyrugu[0].yon = YON_YUKARI;
	}

	if (tuslar['S'] != 0) //harfe basınca aşağı gitmesi için
	{
		yilanKuyrugu[0].yon = YON_ASAGI;
	}

	//yılanın büyümesi için

	if (tuslar['P'] != 0) //harfe basınca aşağı gitmesi için
	{
		yilanKuyrugunaEkle();
	}


}  


int main()
{

	kursoruGizle();
	
	yilanOlustur();

	

	while (true)
	{
		sahneyiTemizle();
		sinirlariolustur();
		klavyeKontrol();

		yilaniHareketEttir();
		yilaniSahneyeYerlestir();

		gotoxy(0, 0);
		sahneyiCiz();
		Sleep(50);
	}

	
}