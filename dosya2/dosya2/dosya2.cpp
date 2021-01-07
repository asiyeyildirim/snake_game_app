#include<iostream>
#include<Windows.h>

// kaynak video:https://www.youtube.com/watch?v=6ondDUDhv6w
using namespace std;

const int genislik = 80; // sabit bir değişken oluşturduk.Nereye kadar gideceğini belirttik
const int yukseklik = 20;
char sahne[genislik][yukseklik];

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
			sahne[x][y]=' ';
		}
		 
	}


}

void sinirlariolustur()
{
	for (int x = 0; x < genislik; x++)
	{
	  sahne[x][0]=219;
	  sahne[x][yukseklik-1] = 219;
	}

	for (int y = 0; y < yukseklik; y++)
	{
		sahne[0][y] = 219;
		sahne[genislik-1][y] = 219;

	}
}


int main()
{
	
	kursoruGizle();
	
	
	gotoxy(0, 0);
	
	int i = 0;
	while (true)
	{
		sahneyiTemizle();
		sinirlariolustur();
		sahne[20+i][10] = 'a';
		gotoxy(0, 0);
		sahneyiCiz();
		Sleep(50);
		i++;
	}
	 
	cin.get();
}