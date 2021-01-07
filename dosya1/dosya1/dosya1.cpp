#include<iostream>
#include<Windows.h>
using namespace std;
// kaynak video=https://www.youtube.com/watch?v=6cfKyV0mjys
const int genislik = 80; // sabit bir değişken oluşturduk.Nereye kadar gideceğini belirttik
const int yukseklik = 20;


//Konum belirtek,koordinatı değiştirmek için windows apı'den yararlanıyoruz.Bunun için fonksiyonu tanımlayalım


void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}




int main()
{
	//soldan sağa doğru a'ları çizme işlemi
	for (int i = 0; i < genislik; i++) {

		cout << "a";

		Sleep(30); //bekleme süresi belirterek çalıştırma.yavaş yavaş

	}

	//a'ları aşağı doğru götürme işlemi

	for (int i = 0; i < yukseklik; i++)
	{

		gotoxy(genislik - 1, i);


		cout << "a";
		Sleep(30); //hepsini aynı anda görmemek için
	}
	//sağdan sola döndürme

	for (int i = 0; i < genislik; i++) {

		gotoxy(genislik - i - 1, yukseklik - 1);

		cout << "a";

		Sleep(30); //bekleme süresi belirterek çalıştırma.yavaş yavaş

	}


	for (int i = 0; i < yukseklik; i++) {

		gotoxy(0, yukseklik - 1 - i);

		cout << "a";

		Sleep(30); //bekleme süresi belirterek çalıştırma.yavaş yavaş

	}



	cin.get();



}
