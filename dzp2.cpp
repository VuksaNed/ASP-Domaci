#include <iostream>
using namespace std;

struct  Listasusednosti
{
	int info;
	Listasusednosti* susedni;

};

Listasusednosti** graf;
int dimenzija = -1;
int vrste, kolone;
int iulaz = -1, jizlaz = -1, iizlaz = -1, julaz = -1;


int konvertuj(int x, int y)
{
	return(x * kolone + y);
}

bool ima(int x, int y)
{
	if (x > y)
	{
		int pom = x;
		x = y;
		y = pom;
	}
	Listasusednosti* novipom = graf[x];
	while ((novipom->susedni != nullptr) && (novipom->susedni->info < y)) novipom = novipom->susedni;
	if (((novipom->susedni != nullptr) && (novipom->susedni->info == y)))
	{
		return true;
	}
	return false;
}

int imap(int x, int y)
{
	if (x > y)
	{
		int pom = x;
		x = y;
		y = pom;
	}
	Listasusednosti* novipom = graf[x];
	while ((novipom->susedni != nullptr) && (novipom->susedni->info < y)) novipom = novipom->susedni;
	if (((novipom->susedni != nullptr) && (novipom->susedni->info == y)))
	{
		return 1;
	}
	return 400000;
}

void napravimatricu(int **d, int **t)
{
	for (int i=1;i<dimenzija+1;i++)
		for (int j = 1; j < dimenzija+1; j++)
		{
			if (i == j)
			{
				d[i][j] = 0;
				t[i][j] = 0;
			}
			if (i < j)
			{
				d[i][j] = imap(i-1, j-1);
				if (d[i][j] == 1) t[i][j] = i;
				else t[i][j] = 0;
			}
			if (i > j)
			{
				d[i][j] = d[j][i];
				if (d[i][j] == 1) t[i][j] = i;
				else t[i][j] = 0;
			}
		}

}

int meni()
{
	while (1)
	{
		cout << "Unesite broj operacije koju zelite da izvrsite" << endl;
		cout << "1. Stvaranje lavirinta na osnovu zadatih dimenzija" << endl;
		cout << "2. Dodaj ulaz i izlaz lavirinta" << endl;
		cout << "3. Dodavanje grane u graf" << endl;
		cout << "4. Brisanje grane iz grafa" << endl;
		cout << "5. Ispis lavirnita" << endl;
		cout << "6. Resavanje lavirnita" << endl;
		cout << "7. Brisanje grafa" << endl;
		cout << "8. Za izlazak iz programa" << endl;
		int x;
		cin >> x;
		if ((x <= 8) && (x >= 1)) return x;
	}
}

void stvorigraf()
{
	if (dimenzija != -1)
	{
		cout << "Graf vec postoji" << endl;
		return;
	}
	int x,y;
	cout << "Unesite dimenzije lavirinta:" << endl;
	cin >> x>>y;
	vrste = x;
	kolone = y;
	dimenzija = vrste * kolone;
	graf = new Listasusednosti * [dimenzija];
	for (int i = 0; i < dimenzija; i++)
	{
		graf[i] = new Listasusednosti();
		graf[i]->susedni = nullptr;
		graf[i]->info = 1;
	}
}

void ulazizlaz()
{
	if (dimenzija == -1)
	{
		cout << "Graf jos nije stvore" << endl;
		return;
	}

	int x1, y1, x2, y2;
	cout << "Unesi kordinate cvorova koje zelis da ti budu ulaz i izlaz" << endl;
	cin >> x1 >> y1;
	cin >> x2 >> y2;

	if (((y1 >= kolone) || (y1 < 0) || (x1 >= vrste) || (x1 < 0)) ||
		((y2 >= kolone) || (y2 < 0) || (x2 >= vrste) || (x2 < 0)))
	{
		cout << "Neispravno uneti parametri";
		return;
	}
	iulaz = x1;
	iizlaz = x2;
	julaz = y1;
	jizlaz = y2;

}

void dodajgranu()
{
	if (dimenzija == -1)
	{
		cout << "Graf jos nije stvore" << endl;
		return;
	}

	int x1, y1, x2, y2;
	cout << "Unesi kordinate cvorova koje zelis da povezes" << endl;
	cin >> x1 >> y1;
	cin >> x2 >> y2;

	if (((x1 >= vrste) || (x1 < 0) || (y1 >= kolone) || (y1 < 0)) ||
		((x2 >= vrste) || (x2 < 0) || (y2 >= kolone) || (y2 < 0)))
	{
		cout << "Neispravno uneti parametri";
		return;
	}

	if (!((((abs(x1 - x2)) == 1) && ((abs(y1 - y2)) == 0)) || (((abs(x1 - x2)) == 0) && ((abs(y1 - y2)) == 1))))
	{
		cout << "Ovi cvorovi se ne mogu povezati" << endl;
		return;
	}

	int x = konvertuj(x1, y1);
	int y = konvertuj(x2, y2);
	if (x > y)
	{
		int pom = x;
		x = y;
		y = pom;
	}

	Listasusednosti* novi = new Listasusednosti;
	novi->info = y;
	novi->susedni = nullptr;
	if ((graf[x]->susedni == nullptr) || (graf[x]->susedni->info > y))
	{
		novi->susedni = graf[x]->susedni;
		graf[x]->susedni = novi;
	}
	else {
		Listasusednosti* novipom = graf[x];
		while ((novipom->susedni != nullptr) && (novipom->susedni->info < y)) novipom = novipom->susedni;
		if (((novipom->susedni != nullptr) && (novipom->susedni->info == y)) || (novipom->info == y))
		{
			cout << "Ova grana vec postoji" << endl;
			return;
		}
		novi->susedni = novipom->susedni;
		novipom->susedni = novi;
	}
}

void obrisigranu()
{
	if (dimenzija == -1)
	{
		cout << "Graf jos nije stvore" << endl;
		return;
	}

	int x1, y1, x2, y2;
	cout << "Unesi kordinate cvorova koje zelis da povezes" << endl;
	cin >> x1 >> y1;
	cin >> x2 >> y2;

	if (((x1 >= vrste) || (x1 < 0) || (y1 >= kolone) || (y1 < 0)) ||
		((x2 >= vrste) || (x2 < 0) || (y2 >= kolone) || (y2 < 0)))
	{
		cout << "Neispravno uneti parametri";
		return;
	}

	int x = konvertuj(x1, y1);
	int y = konvertuj(x2, y2);
	if (x > y)
	{
		int pom = x;
		x = y;
		y = pom;
	}

	if (graf[x]->susedni == nullptr)
	{
		cout << "Ova grana ne postoji " << endl;
		return;
	}

	Listasusednosti* novipom = graf[x]->susedni;
	if (graf[x]->susedni->info == y)
	{
		graf[x]->susedni = graf[x]->susedni->susedni;
		delete novipom;
	}
	else
	{

		while (((novipom->susedni) && (novipom->susedni->info != y)) && !(novipom->susedni->info > y)) novipom = novipom->susedni;

		if ((novipom->susedni == nullptr) || (novipom->susedni->info > y))
		{
			cout << "Ova grana ne postoji " << endl;
			return;
		}

		if (novipom->susedni->susedni == nullptr)
		{
			Listasusednosti* novip = novipom->susedni;
			novipom->susedni = nullptr;
			delete novip;
		}
		else
		{
			Listasusednosti* novip = novipom->susedni;
			novipom->susedni = novip->susedni;
			delete novip;
		}
	}
}

void ispis()
{
	if (dimenzija == -1)
	{
		cout << "Graf jos nije stvore" << endl;
		return;
	}

	cout << endl;
	for (int i = 0; i < kolone * 2 + 1; i++)
	{
		if ((iulaz == 0) && (i % 2 == 1) && (julaz == i / 2)) cout << "U";
		else if ((iizlaz == 0) && (i % 2 == 1) && (jizlaz == i / 2)) cout << "X";
				else cout << "*";
	}

	cout << endl;

	for (int i = 0; i < vrste*2-1; i++)
	{
		if ((julaz == 0) && (i % 2 == 0) && (iulaz == i / 2)&&(iulaz!=0) && (iulaz != vrste-1)) cout << "U";
		else if ((jizlaz == 0) && (i % 2 == 0) && (iizlaz == i / 2) && (iizlaz != 0) && (iizlaz != vrste - 1)) cout << "X";
			else cout << "*";
		for (int j = 0; j < kolone * 2-1; j++)
		{
			if ((i % 2) == 0)
			{
				if ((j % 2) == 0)
				{
					cout << "O";
				}
				else
				{
					int x = konvertuj(i / 2, j / 2);
					int y = konvertuj(i / 2, j / 2+1);
					if (ima(x, y)) cout << " ";
					else cout << "*";
				}
			}
			else
			{
				if ((j % 2) == 1)
				{
					cout << "*";
				}
				else
				{
					int x = konvertuj(i / 2, j / 2);
					int y = konvertuj(i / 2 + 1, j / 2 );
					if (ima(x, y)) cout << " ";
					else cout << "*";
				}

			}

		}
		if ((julaz == kolone-1) && (i % 2 == 0) && (iulaz == i / 2) && (iulaz != vrste-1) && (iulaz != 0)) cout << "U";
		else if ((jizlaz == kolone-1) && (i % 2 == 0) && (iizlaz == i / 2) && (iizlaz != vrste - 1) && (iizlaz != 0)) cout << "X";
			else cout << "*";
		cout << endl;
	}

	for (int i = 0; i < kolone * 2+1; i++) 
		if ((iulaz == vrste-1) && (i % 2 == 1) && (julaz == i / 2)) cout << "U";
		else if ((iizlaz == vrste-1) && (i % 2 == 1) && (jizlaz == i / 2)) cout << "X";
				else cout << "*";

	cout << endl;
}

void resi()
{
	if ((dimenzija == -1) || (iulaz == -1))
	{
		cout << "Lavirint ne postoji"<<endl;
		return;
	}

	int **d=new int*[dimenzija+1];
	int** t = new int* [dimenzija+1];
	for (int i = 1; i < dimenzija+1; i++)
	{
		d[i] = new int[dimenzija+1];
		t[i] = new int[dimenzija+1];
	}
	napravimatricu(d,t);
	
	for (int k=1; k<dimenzija+1;k++)
		for (int i = 1; i < dimenzija+1; i++)
			for (int j = 1; j < dimenzija+1; j++)
				if ((d[i][j] > d[i][k] + d[k][j]))
				{
					t[i][j] = t[k][j];
					d[i][j] = d[i][k] + d[k][j];
				}
	

	int j = konvertuj(iulaz, julaz)+1;
	int i = konvertuj(iizlaz, jizlaz) + 1;
	int x;
	int y;
	while (i != j)
	{
		if (t[i][j] == 0)
		{
			cout << "Ne puta do izlaza";
			return;
		}
		else
		{
			y=(j-1)%kolone;
			x=(j-1)/kolone;
			cout << "(" << x << "," << y << ")->";
			j = t[i][j];
		}
	}
	y = (j - 1) % kolone;
	x = (j - 1) / kolone;
	cout << "(" << x << "," << y << ")"<<endl;
}

void obrisi()
{
	for (int i = 0; i < dimenzija; i++)
	{
		if (graf[i]->info != -1)
		{
			Listasusednosti* pom = graf[i];
			Listasusednosti* preth = nullptr;
			while (pom)
			{
				preth = pom;
				pom = pom->susedni;
				delete preth;
			}
			delete pom;
		}
	}
	delete[]graf;
	dimenzija = -1;
	iulaz = -1;
	iizlaz = -1;
	julaz = -1;
	jizlaz = -1;
}

int main()
{
	int instrukcija;
	while (1)
	{
		instrukcija = meni();
		switch (instrukcija)
		{
		case 1:
			stvorigraf();
			break;
		case 2:
			ulazizlaz();
			break;
		case 3:
			dodajgranu();
			break;
		case 4:
			obrisigranu();
			break;
		case 5:
			ispis();
			break;
		case 6:
			resi();
			break;
		case 7:
			obrisi();
			break;
		case 8:
			return 0;
		}
	}
}