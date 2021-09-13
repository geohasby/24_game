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
	
	cout<<"                               P E R M A I N A N   D U A   E M P A T                               "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"                                            Created by :                                           "<<endl;
	cout<<"                                     GEOHASBY AMMAR KAUTSAR                                        "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"      --------------------------- APA ITU PERMAINAN DUA EMPAT ? -------------------------------    "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Pada dasarnya, permainan dua empat adalah permainan kartu remi.                     |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Dalam permainan ini biasanya terdiri dari banyak pemain.                            |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Permainan diawali dengan mengocok kartu, lalu dibuka 4 kartu acak.                  |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Sebelumnya kartu King, Queen, dan Jack dikeluarkan dari deck terlebih dahulu.       |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Dari keempat kartu yang terbuka pemain menyusun cara penyelesaian agar hasilnya 24, |   "<<endl;
	cout<<"     |     bisa menggunakan operasi tambah (+), kurang (-), kali (*), dan bagi (/).            |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Pemain tercepat yang berhasil menemukan cara penyelesaiannya adalah pemenangnya.    |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Permainan sederhana ini bisa meelatih arithmetical mental dan fast thinking.        |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"      ------------------------ Selamat Bermain, Selamat Menikmati -----------------------------    "<<endl<<endl<<endl<<endl<<endl;
	cout<<"                          Tekan 'Spasi' untuk membaca aturan permainan";
	
	do{
		a = getch();
	}while (a!=' ');
	system("cls");
	
	cout<<"                               P E R M A I N A N   D U A   E M P A T                               "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"                                            Created by :                                           "<<endl;
	cout<<"                                     GEOHASBY AMMAR KAUTSAR                                        "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"                                                                                                   "<<endl;
	cout<<"      --------------------------------- ATURAN PERMAINAN --------------------------------------    "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Permainan ini memiliki beberapa level dengan batasan waktu yang berbeda-beda.       |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Pemain yang berhasil menyelesaikan suatu level dalam jangka waktu yang ditentukan,  |   "<<endl;
	cout<<"     |     berhak lanjut ke level berikutnya, jika tidak maka  G A M E  O V E R.               |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Format input : indeks_kartu_pertama  tanda_operasi_hitung  indeks_kartu_kedua       |   "<<endl;
	cout<<"     |     Contoh       : 1/2                                                                  |   "<<endl;
	cout<<"     |     maka nilai kartu ke-1 akan dibagi dengan nilai kartu ke-2,                          |   "<<endl;
	cout<<"     |     dan kartu ke-2 akan hangus (tidak bisa digunakan lagi).                             |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Untuk operasi pembagian, hanya bisa dilakukan jika   x % y = 0   dan   y != 0       |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Tidak ada UNDO.                                                                     |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > Jika ingin tahu cara penyelesaiannya, input '?', tetapi  G A M E  O V E R.          |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"     |   > INGAT!!!, yang diinputkan adalah indeks kartu, bukan nilai kartunya.                |   "<<endl;
	cout<<"     |                                                                                         |   "<<endl;
	cout<<"      ------------------------ Selamat Bermain, Selamat Menikmati -----------------------------    "<<endl<<endl;
	cout<<"                              Tekan 'Spasi' untuk memulai permainan";
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

