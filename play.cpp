#include<bits/stdc++.h>
#include<conio.h>
#include<windows.h>
#include<ctime>
#define pixel kartu[now].bentuk
#define negatif 999
#define add solution[jumlah_solusi] +=
using namespace std;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

struct card
{
	int nilai;
	char bentuk[11][24];
};

clock_t start;
card kartu[4];
string nama, solution[1000];
int x, y, jumlah_solusi, level, operasi_ke = 0, limit = 60, urutanangka[4];
char z, tanda[4], simbol[] = {'+','-','*','/'};
bool life = 1, tersedia[4];

int hitung(int x, int y, char z)
{
	if(z == '+')
		return x+y;
	else if(z == '-')
		return x-y;
	else if(z == '*')
		return x*y;
	else if(z == '/')
	{
		if(y == 0 or x % y != 0)				
			return 999;
		else return x/y;
	}
}

void operation()
{
	if(hitung(hitung(hitung(urutanangka[0], urutanangka[1], tanda[0]), urutanangka[2], tanda[1]), urutanangka[3], tanda[2]) == 24.0){
		solution[jumlah_solusi] = "((";
		add char(urutanangka[0] + 48);
		add tanda[0];
		add char(urutanangka[1] + 48);
		add ')';
		add tanda[1];
		add char(urutanangka[2] + 48);
		add ')';
		add tanda[2];
		add char(urutanangka[3] + 48);
		add " = 24";
		jumlah_solusi++;
	}
	if(hitung(hitung(urutanangka[0], urutanangka[1], tanda[0]), hitung(urutanangka[2], urutanangka[3], tanda[2]), tanda[1]) == 24.0){
		solution[jumlah_solusi] = "(";
		add char(urutanangka[0] + 48);
		add tanda[0];
		add char(urutanangka[1] + 48);
		add ')';
		add tanda[1];
		add '(';
		add char(urutanangka[2] + 48);
		add tanda[2];
		add char(urutanangka[3] + 48);
		add ") = 24";
		jumlah_solusi++;
	}
	if(hitung(hitung(urutanangka[0], hitung(urutanangka[1], urutanangka[2], tanda[1]), tanda[0]), urutanangka[3], tanda[2]) == 24.0){
		solution[jumlah_solusi] = "(";
		add char(urutanangka[0] + 48);
		add tanda[0];
		add '(';
		add char(urutanangka[1] + 48);
		add tanda[1];
		add char(urutanangka[2] + 48);
		add "))";
		add tanda[2];
		add char(urutanangka[3] + 48);
		add " = 24";
		jumlah_solusi++;
	}
	if(hitung(urutanangka[0], hitung(hitung(urutanangka[1], urutanangka[2], tanda[1]), urutanangka[3], tanda[2]), tanda[0]) == 24.0){
		solution[jumlah_solusi] = char(urutanangka[0] + 48);
		add tanda[0];
		add "((";
		add char(urutanangka[1] + 48);
		add tanda[1];
		add char(urutanangka[2] + 48);
		add ')';
		add tanda[2];
		add char(urutanangka[3] + 48);
		add ") = 24";
		jumlah_solusi++;
	}
	if(hitung(urutanangka[0], hitung(urutanangka[1], hitung(urutanangka[2], urutanangka[3], tanda[2]), tanda[1]), tanda[0]) == 24.0){
		solution[jumlah_solusi] = char(urutanangka[0] + 48);
		add tanda[0];
		add '(';
		add char(urutanangka[1] + 48);
		add tanda[1];
		add '(';
		add char(urutanangka[2] + 48);
		add tanda[2];
		add char(urutanangka[3] + 48);
		add ")) = 24";
		jumlah_solusi++;
	}
}

void random_urutan_angka()
{
	for(int a=0; a<4; a++)
		for(int b=0; b<4; b++)
		{
			if(b==a) continue;
			for(int c=0; c<4; c++)
			{
				if(c==a or c==b) continue;
				for(int d=0; d<4; d++)
				{
					if(d==a or d==b or d==c) continue;

					urutanangka[0] = kartu[a].nilai;
					urutanangka[1] = kartu[b].nilai;
					urutanangka[2] = kartu[c].nilai;
					urutanangka[3] = kartu[d].nilai;

					operation();
				}
			}
		}
}

void menentukan_tanda_operasi_hitung()
{
	for(int a=0; a<4; a++)					
		for(int b=0; b<4; b++)				
			for(int c=0; c<4; c++)			
			{
				tanda[0] = simbol[a];		//untuk operasi hitung kartu 1 dan 2
				tanda[1] = simbol[b];		//untuk operasi hitung kartu 2 dan 3
				tanda[2] = simbol[c];		//untuk operasi hitung kartu 3 dan 4
				
				random_urutan_angka();
			}
}

void find_solution()
{
	menentukan_tanda_operasi_hitung();
}

void cetak_sebagian(int x, int y)
{	
	for(int a=0; a<11; a++)
	{
	    SetConsoleCursorPosition(h, {3+(x*26), 5+a});
	    for(int b=0; b<24; b++)	cout<<kartu[x].bentuk[a][b];
		
		SetConsoleCursorPosition(h, {3+(y*26), 5+a});
	    for(int b=0; b<24; b++) cout<<kartu[y].bentuk[a][b];
	}
}

void cetak_kartu()
{
	cout<<"\n   ----------------------------------------------- LEVEL "<<level<<" ----------------------------------------------   \n\n";
	cout<<"                                              SISA WAKTU =   \n\n";
	for(int a=0; a<11; a++)
	{
		cout<<"   ";
		for(int b=0; b<24; b++) cout<<kartu[0].bentuk[a][b];
		cout<<"  ";
		for(int b=0; b<24; b++) cout<<kartu[1].bentuk[a][b];
		cout<<"  ";
		for(int b=0; b<24; b++) cout<<kartu[2].bentuk[a][b];
		cout<<"  ";
		for(int b=0; b<24; b++) cout<<kartu[3].bentuk[a][b];
		cout<<endl;
	}
	cout<<endl;
}

void timer()
{ 
	int duration=0,temp=0;
	while(!kbhit())
	{
		duration = (clock() - start) / CLOCKS_PER_SEC;
		if(duration > temp)
		{
	    	SetConsoleCursorPosition(h, {59, 3});
			if(limit - duration < 10)
				cout<<limit - duration<<' ';
			else cout<<limit - duration;
	    	SetConsoleCursorPosition(h, {52, 17});
		}
		temp = duration;
	    
		if(duration > limit)
		{
			system("cls");
			system("color 4");
			cout<<endl<<endl;
			cout<<"      -----------------------------------------------------------------------------------------    "<<endl;
			cout<<"     |                                                                                         |   "<<endl;
			cout<<"     |                                 G  A  M  E    O  V  E  R                                |   "<<endl;
			cout<<"     |                                                                                         |   "<<endl;
			cout<<"     |                                      Waktu Habis !                                      |   "<<endl;
			cout<<"     |                                                                                         |   "<<endl;
			cout<<"     |                                      HIGHSCORE = "<<level<<"                                      |   "<<endl;
			cout<<"     |                                                                                         |   "<<endl;
			cout<<"     |                 Screenshot and share, Let them know how pro you are !!!                 |"<<endl;
			cout<<"     |                                                                                         |   "<<endl;
			cout<<"      -----------------------------------------------------------------------------------------    "<<endl;
			getch();
			exit(0);
		}
	}
	
}

void game_over()
{
	SetConsoleTextAttribute(h, 3);
	cout<<endl<<endl
	<<endl;
	cout<<"   -------------------------------  C A R A   P E N Y E L E S A I A N  --------------------------------    "<<endl<<endl;
	cout<<"   ";
	
	for(int a=0; a<jumlah_solusi; a++)
	{
		cout<<solution[a];
		if(a % 5 == 4) cout<<"\n   ";
		else cout<<"     ";
	}
	
	getch();
	
	system("cls");
	system("color 4");
	cout<<endl<<endl;
	cout<<"      -----------------------------------------------------------------------------------------    "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |                                 G  A  M  E    O  V  E  R                                |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |                                      HIGHSCORE = "<<level<<"                                      |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |                 Screenshot and share, Let them know how pro you are !!!                 |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"      -----------------------------------------------------------------------------------------    "<<endl;
	getch();
}

void print_time()
{
	SetConsoleCursorPosition(h, {59, 3});
	cout<<limit - ((clock() - start) / CLOCKS_PER_SEC);
	SetConsoleCursorPosition(h, {52, 17});
}

void cek_kondisi()
{
	if(kartu[x-1].nilai == 24 and life)
	{
		system("color 2");
		cout<<endl<<endl<<"                                      C O N G R A T U L A T I O N !!!"<<endl;
		print_time();
		getch();
		system("cls");
	}
	else
	{
		life = 0;
		system("color 4");
		cout<<endl<<"                                          W R O N G   A N S W E R"<<endl;
		print_time();
		getch();
	}
}

void bentuk_angka(int x, int y, int now, int angka)
{
	if(angka == 0){
		for(int a=1; a<=3; a++)
		{
			pixel[x+a][y] = char(186);
			pixel[x+a][y+3] = char(186); 
		}
		
		for(int a=1; a<=2; a++)
		{
			pixel[x+0][y+a] = char(205);
			pixel[x+4][y+a] = char(205);
		}
		
		pixel[x][y] = char(201);
		pixel[x][y+3] = char(187);
		pixel[x+4][y] = char(200);
		pixel[x+4][y+3] = char(188);
	}
	else if(angka == 1){
		for(int a=1; a<=3; a++)
			pixel[x+a][y+2] = char(186);
		
		for(int a=1; a<=3; a+=2)
			pixel[x+4][y+a] = char(205);
		
		pixel[x+0][y+2] = char(187);
		pixel[x+0][y+1] = char(205);
		pixel[x+4][y+2] = char(202);
		
	}
	else if(angka == 2){
		for(int a=0; a<=4; a+=2)
			for(int b=1; b<=2; b++)
				pixel[x+a][y+b] = char(205);
		
		pixel[x][y] = char(205);
		pixel[x+4][y+3] = char(205);
		pixel[x+1][y+3] = char(186);
		pixel[x+3][y] = char(186);
		pixel[x][y+3] = char(187);
		pixel[x+2][y] = char(201);
		pixel[x+2][y+3] = char(188);
		pixel[x+4][y] = char(200);
		
	}
	else if(angka == 3){
		for(int a=0; a<=4; a+=2)	
			for(int b=0; b<=2; b++)
				pixel[x+a][y+b] = char(205);
		
		pixel[x+1][y+3] = char(186);
		pixel[x+3][y+3] = char(186);
		pixel[x][y+3] = char(187);
		pixel[x+2][y+3] = char(185);
		pixel[x+4][y+3] = char(188);
	}
	else if(angka == 4){
		for(int a=0; a<=4; a++)
		{
			if(a<2) pixel[x+a][y] = char(186);
			pixel[x+a][y+3] = char(186);
		}
		
		pixel[x+2][y+1] = char(205);
		pixel[x+2][y+2] = char(205);
		pixel[x+2][y] = char(200);
		pixel[x+2][y+3] = char(185);
	}
	else if(angka == 5){
		for(int a=0; a<=4; a+=2)
			for(int b=0; b<=3; b++)
				pixel[x+a][y+b] = char(205);
		
		pixel[x+1][y] = char(186);
		pixel[x+3][y+3] = char(186);
		pixel[x][y] = char(201);
		pixel[x+2][y] = char(200);
		pixel[x+2][y+3] = char(187);
		pixel[x+4][y+3] = char(188);
		
	}
	else if(angka == 6){
		for(int a=0; a<=4; a+=2)
			for(int b=1; b<=3; b++)
				pixel[x+a][y+b] = char(205);
		
		pixel[x+1][y] = char(186);
		pixel[x+3][y] = char(186);
		pixel[x+3][y+3] = char(186);
		pixel[x][y] = char(201);
		pixel[x+2][y] = char(204);
		pixel[x+4][y] = char(200);
		pixel[x+2][y+3] = char(187);
		pixel[x+4][y+3] = char(188);
	}
	else if(angka == 7){
		for(int a=0; a<=2; a++)
			pixel[x][y+a] = char(205);
		for(int a=1; a<=4; a++)
			pixel[x+a][y+3] = char(186);
		pixel[x][y+3] = char(187);
	}
	else if(angka == 8){
		for(int a=0; a<=4; a+=2)
			for(int b=1; b<=2; b++)
				pixel[x+a][y+b] = char(205);
		
		for(int a=1; a<=3; a+=2)
			for(int b=0; b<=3; b+=3)
				pixel[x+a][y+b] = char(186);
		
		pixel[x][y] = char(201);
		pixel[x+2][y] = char(204);
		pixel[x+4][y] = char(200);
		pixel[x][y+3] = char(187);
		pixel[x+2][y+3] = char(185);
		pixel[x+4][y+3] = char(188);
	}
	else if(angka == 9){
		for(int a=0; a<=4; a+=2)
			for(int b=1; b<=2; b++)
				pixel[x+a][y+b] = char(205);
		
		for(int a=1; a<=3; a+=2)
			for(int b=0; b<=3; b+=3)
				pixel[x+a][y+b] = char(186);
		
		pixel[x+3][y] = ' ';
		pixel[x][y] = char(201);
		pixel[x+2][y] = char(200);
		pixel[x+4][y] = char(205);
		pixel[x][y+3] = char(187);
		pixel[x+2][y+3] = char(185);
		pixel[x+4][y+3] = char(188);
	}
	else if(angka == negatif){
		for(int a=1; a<4; a++)
			pixel[x][y+a] = char(205);
	}
}

void buat_bentuk(int now)
{
	for(int a=1; a<=9; a++)
		for(int b=1; b<=22; b++)
			pixel[a][b] = ' ';				//semua elemennya kuisi spasi
	
	pixel[0][11] = char(now+49);			//indeks kartu
		
	if(kartu[now].nilai >= 1000)			//nilai kartu 4 digit
	{
		bentuk_angka(3, 2, now, kartu[now].nilai / 1000);				//digit pertama
		bentuk_angka(3, 7, now, (kartu[now].nilai % 1000) / 100);		//digit kedua
		bentuk_angka(3, 12, now, (kartu[now].nilai % 100) / 10);		//digit ketiga
		bentuk_angka(3, 17, now, kartu[now].nilai % 10);				//digit keempat
	}	
	else if(kartu[now].nilai >= 100)		//nilai kartu 3 digit
	{
		bentuk_angka(3, 4, now, kartu[now].nilai / 100);			//digit pertama
		bentuk_angka(3, 10, now, (kartu[now].nilai % 100) / 10);	//digit kedua
		bentuk_angka(3, 16, now, kartu[now].nilai % 10);			//digit ketiga
	}
	else if(kartu[now].nilai >= 10)			//nilai kartu 2 digit
	{
		bentuk_angka(3, 7, now, kartu[now].nilai / 10);		//digit pertama
		bentuk_angka(3, 13, now, kartu[now].nilai % 10);	//digit kedua
	}
	else if(kartu[now].nilai <= -100)		//nilai kartu negatif 3 digit
	{
		bentuk_angka(5, 2, now, negatif);									//simbol negatif
		bentuk_angka(3, 7, now, (kartu[now].nilai * -1) / 100);				//digit pertama
		bentuk_angka(3, 12, now, ((kartu[now].nilai * -1) % 100) / 10);		//digit kedua
		bentuk_angka(3, 17, now, (kartu[now].nilai * -1) % 10);				//digit ketiga
	}
	else if(kartu[now].nilai <= -10)		//nilai kartu negatif 2 digit
	{
		bentuk_angka(5, 4, now, negatif);							//simbol negatif
		bentuk_angka(3, 10, now, (kartu[now].nilai * -1) / 10);		//digit pertama
		bentuk_angka(3, 16, now, (kartu[now].nilai * -1) % 10);		//digit kedua
	}
	else if(kartu[now].nilai < 0)			//nilai kartu negatif 1 digit
	{
		bentuk_angka(5, 7, now, negatif);							//simbol negatif
		bentuk_angka(3, 13, now, (kartu[now].nilai * -1) % 10);		//digit pertama
	}
	else bentuk_angka(3, 10, now, kartu[now].nilai);	//nilai kartu 1 digit
}

void gabung(int x, int y, int i, char z)
{
	if(x<y)
		for(int a=23; a>=0; a--)
		{
			kartu[x].bentuk[0][a] = char(176+i);
			kartu[x].bentuk[10][a] = char(176+i);
			for(int b=0; b<11; b++)
			{
				for(int c=0; c<24; c++)
					if(c<a) kartu[y].bentuk[b][c] = kartu[y].bentuk[b][c+1];
					else kartu[y].bentuk[b][c] = ' ';
				
				if(a==0 or a==23)
					kartu[x].bentuk[b][a] = char(176+i);
			}
			cetak_sebagian(x,y);
		}
	else
		for(int a=0; a<24; a++)
		{
			kartu[x].bentuk[0][a] = char(176+i);
			kartu[x].bentuk[10][a] = char(176+i);
			for(int b=0; b<11; b++)
			{
				for(int c=23; c>=0; c--)
					if(c>a) kartu[y].bentuk[b][c] = kartu[y].bentuk[b][c-1];
					else kartu[y].bentuk[b][c] = ' ';
				
				if(a==0 or a==23)
					kartu[x].bentuk[b][a] = char(176+i);
			}
			cetak_sebagian(x,y);
		}
	
	if(z == '+') kartu[x].nilai += kartu[y].nilai;
	else if(z == '-') kartu[x].nilai -= kartu[y].nilai;
	else if(z == '*') kartu[x].nilai *= kartu[y].nilai;
	else if(z == '/') kartu[x].nilai /= kartu[y].nilai;
	
	buat_bentuk(x);
	system("CLS");
	cetak_kartu();
}

void inputan()
{
	char dummy;
	bool input_valid;
	
	for(int a=0; a<3; a++)
	{
		input_valid = 0;
		while(input_valid == 0)
		{
			timer();
			cin>>dummy;			
			if(dummy == '?')
			{
				life = 0;
				game_over();
				exit(0);
			}
			else
			{
				x = int(dummy) - 48;
				cin>>z>>y;
			}
			
			if(tersedia[x-1]==1 and tersedia[y-1]==1 and x!=y and x>=1 and x<=4 and y>=1 and y<=4 and (z == '+' or z == '-' or z=='*' or z=='/'))
				input_valid = 1;
			
			if(z == '/' and (kartu[y-1].nilai == 0 or kartu[x-1].nilai % kartu[y-1].nilai != 0))
				input_valid = 0;
				
			if(input_valid == 0)
			{
				SetConsoleTextAttribute(h, 4);		//font color -> red
				cout<<"\n                                   Input tidak valid, Mohon ulangi lagi"<<endl;
				SetConsoleTextAttribute(h, 15);		//font color -> white
				timer();
				getch();
				system("cls");
				cetak_kartu();
			}
		}
		
		tersedia[y-1] = 0;				//kartu kedua hangus alias sudah tidak tersedia
		if(a==2) operasi_ke=42;			
		gabung(x-1,y-1,++operasi_ke,z);	//animasi penggabungan
	}
}

void make_border(int now)
{
	for(int a=0; a<11; a++)
		for(int b=0; b<24; b++)
			if(a == 0 or a == 10 or b == 0 or b == 23)
				pixel[a][b] = char(176);
}

void random_angka()
{
	do
	{
		for(int a=0; a<4; a++)
		{
			kartu[a].nilai = rand() % 9 + 1;
			make_border(a);
			buat_bentuk(a);
			tersedia[a] = 1;					//semua kartu awalnya tersedia
		}
		find_solution();						//cek terlebih dahulu bisa disolve tidak
	} while(jumlah_solusi == 0);				//jika solusi = 0 atau tidak memiliki solusi maka ulangi
}

void intro()
{
	char a;
	
	cout<<"                                           2 4   G A M E                                           "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"                                            Created by :                                           "<<endl;
	cout<<"                                     GEOHASBY AMMAR KAUTSAR                                        "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"      --------------------------------- WHAT IS 24 GAME ? -------------------------------------    "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Basically, 24 game is a playing card games                                          |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > This game is usually played by many players                                         |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Before starting the game, get rid of the king-queen-jack cards from the deck first  |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > The game starts by shuffling the cards, then open 4 random cards                    |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > From the numbers of the 4 cards opened, players should arrange aritmethic operation |   "<<endl;
	cout<<"     |     so that the result is 24                                                            |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Aritmethic operations that are allowed are addition (+), subtraction (-),           |   "<<endl;
	cout<<"     |     multiplication (*) and division (/)                                                 |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > The fastest player who finds the solution is the winner                             |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"      -------------------------------- Good Luck Have Fun -------------------------------------    "<<endl<<endl<<endl<<endl;
	cout<<"                              Press 'Space' to read the game rules                                 ";
	
	do{
		a = getch();
	}while (a!=' ');
	system("cls");
	
	cout<<"                                           2 4   G A M E                                           "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"                                            Created by :                                           "<<endl;
	cout<<"                                     GEOHASBY AMMAR KAUTSAR                                        "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"      ------------------------------------ GAME RULES -----------------------------------------    "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > This game has many levels with different time limits                                |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Players who successfully complete a level within the time limit,                    |   "<<endl;
	cout<<"     |     can go to the next level, otherwise   G A M E  O V E R                              |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Input format : card_index  aritmethic_operation_symbol  card_index                  |   "<<endl;
	cout<<"     |     example      : 1/2                                                                  |   "<<endl;
	cout<<"     |     that means the value of the first card divided by the value off the second card     |   "<<endl;
	cout<<"     |     the second card will be forfeited and can't be used anymore                         |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > For the division operation, can only be done if   (x % y = 0)   and   (y != 0)      |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > There is no UNDO                                                                    |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > If you wanna know the solution, type '?', but it will be  G A M E  O V E R          |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Remember!!! Don't input the value of the card, input the index of the card          |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"      -------------------------------- Good Luck Have Fun -------------------------------------    "<<endl<<endl;
	cout<<"                                Press 'Space' to start the game                                    ";
	do{
		a = getch();
	}while (a!=' ');
	system("cls");
}

int main()
{
	srand(time(NULL));			//supaya randomnya berbeda

	intro();
	
	level = 0;					//starting level = 0
	
	while(life)
	{
		jumlah_solusi = 0;
		operasi_ke = 0;			//sudah melakukan operasi hitung 0 kali
		system("color F");		//font color -> white
	
		random_angka();			//ngerandom 4 angka
		
		cetak_kartu();
		
		start = clock();
		
		print_time();
		
		inputan();
		
		cek_kondisi();
		
		if(life == 0) game_over();
		
		level++;
		limit-=5;
	}
}

