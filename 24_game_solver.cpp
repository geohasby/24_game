#include<bits/stdc++.h>
#include<conio.h>
using namespace std;

int angka[4];
int urutanangka[4];
char tanda[3], simbol[] = {'+','-','*','/'};
bool check;

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
		if(y == 0)
			return 999;
		else if(x % y != 0)
			return 999;
		else return x/y;
	}
}

void operation()
{
	if(hitung(hitung(hitung(urutanangka[0], urutanangka[1], tanda[0]), urutanangka[2], tanda[1]), urutanangka[3], tanda[2]) == 24.0){
		check = true;
		cout<<"(("<<urutanangka[0]<<tanda[0]<<urutanangka[1]<<')'<<tanda[1]<<urutanangka[2]<<')'<<tanda[2]<<urutanangka[3]<<" = 24"<<endl;
	}
	
	if(hitung(hitung(urutanangka[0], urutanangka[1], tanda[0]), hitung(urutanangka[2], urutanangka[3], tanda[2]), tanda[1]) == 24.0){
		check = true;
		cout<<"("<<urutanangka[0]<<tanda[0]<<urutanangka[1]<<')'<<tanda[1]<<'('<<urutanangka[2]<<tanda[2]<<urutanangka[3]<<") = 24"<<endl;
	}

	if(hitung(hitung(urutanangka[0], hitung(urutanangka[1], urutanangka[2], tanda[1]), tanda[0]), urutanangka[3], tanda[2]) == 24.0){
		check = true;
		cout<<"("<<urutanangka[0]<<tanda[0]<<'('<<urutanangka[1]<<tanda[1]<<urutanangka[2]<<"))"<<tanda[2]<<urutanangka[3]<<" = 24"<<endl;
	}

	if(hitung(urutanangka[0], hitung(hitung(urutanangka[1], urutanangka[2], tanda[1]), urutanangka[3], tanda[2]), tanda[0]) == 24.0){
		check = true;
		cout<<urutanangka[0]<<tanda[0]<<"(("<<urutanangka[1]<<tanda[1]<<urutanangka[2]<<')'<<tanda[2]<<urutanangka[3]<<") = 24"<<endl;
	}

	if(hitung(urutanangka[0], hitung(urutanangka[1], hitung(urutanangka[2], urutanangka[3], tanda[2]), tanda[1]), tanda[0]) == 24.0){
		check = true;
		cout<<urutanangka[0]<<tanda[0]<<'('<<urutanangka[1]<<tanda[1]<<'('<<urutanangka[2]<<tanda[2]<<urutanangka[3]<<")) = 24"<<endl;
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

					urutanangka[0] = angka[a];
					urutanangka[1] = angka[b];
					urutanangka[2] = angka[c];
					urutanangka[3] = angka[d];

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
				tanda[0] = simbol[a];
				tanda[1] = simbol[b];
				tanda[2] = simbol[c];
				
				random_urutan_angka();
			}
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	cout<<"Input 4 numbers :"<<endl;
	
	while(cin>>angka[0]>>angka[1]>>angka[2]>>angka[3])
	{
		check = false;
		menentukan_tanda_operasi_hitung();
		
		if(check == false)
			cout<<"No solution found"<<endl;
		
		cout<<endl;
		
		cout<<"Input 4 numbers :"<<endl;
	}
}

