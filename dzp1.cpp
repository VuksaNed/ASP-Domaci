#include <iostream>
using namespace std;


struct  Listasusednosti
{
	int info;
	Listasusednosti* susedni;

};

Listasusednosti** graf;
int dimenzija=-1;

int meni()
{
	while (1)
	{
		cout << "Unesite broj operacije koju zelite da izvrsite" << endl;
		cout << "1. Stvaranje grafa na osnovu zadate dimenzije" << endl;
		cout << "2. Dodavanje cvora u graf" << endl;
		cout << "3. Brisanje cvora iz grafa" << endl;
		cout << "4. Dodavanje grane u graf" << endl;
		cout << "5. Brisanje grane iz grafa" << endl;
		cout << "6. Ispis reprezentacije grafa" << endl;
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
	int n;
	cout << "Unesite broj cvorova:" << endl;
	cin >> n;
	if (n<1)
	{
		cout << "Graf vec postoji" << endl;
		return;
	}
	graf = new Listasusednosti*[n];
	dimenzija = n;
	for (int i = 0; i < n; i++)
	{
		graf[i] = new Listasusednosti();
		graf[i]->susedni = nullptr;
		graf[i]->info = 1;
	}
}

void dodajcvor()
{
	if (dimenzija == -1)
	{
		cout << "Graf jos nije stvore" << endl;
		return;
	}

	dimenzija++;
	Listasusednosti** pomocna = new Listasusednosti * [dimenzija];
	for (int i = 0; i < dimenzija-1; i++)
	{
		pomocna[i] = graf[i];
	}
	pomocna[dimenzija - 1] = new Listasusednosti();
	pomocna[dimenzija - 1]->susedni = nullptr;
	pomocna[dimenzija - 1]->info = 1;
	graf = pomocna;
}

void obrisigranu(int x, int y); //deklaracija

void brisanjecvora()
{
	int x;
	cout << "Unesite cvor koji zelite da obrisete"<<endl;
	cin >> x;
	if ((graf[x]->info == -1)||(x >= dimenzija) || (x < 0))
	{
		cout << "Cvor ne postoji"<<endl;
		return;
	}
	while (graf[x]->susedni) 
		obrisigranu(x, graf[x]->susedni->info);
	graf[x]->info = -1;
}

void dodajgranu()
{
	if (dimenzija == -1)
	{
		cout << "Graf jos nije stvore" << endl;
		return;
	}

	int x, y;
	cout << "Unesi koje cvorove zelis da povezes" << endl;
	cin >> x >> y;

	if (((x >= dimenzija) || (x < 0) || (y >= dimenzija) || (y < 0))||(graf[x]->info!=1)||(graf[y]->info!=1))
	{
		cout << "Neispravno uneti parametri"<<endl;
		return;
	}

	Listasusednosti* novi = new Listasusednosti;
	novi->info = y;
	novi->susedni = nullptr;
	if ((graf[x]->susedni == nullptr)||(graf[x]->susedni->info>y))
	{
		novi->susedni = graf[x]->susedni;
		graf[x]->susedni = novi;
	}
	else {
			Listasusednosti* novipom = graf[x];
			while ((novipom->susedni!=nullptr)&&(novipom->susedni->info<y)) novipom = novipom->susedni;
			if (((novipom->susedni != nullptr) && (novipom->susedni->info == y))||(novipom->info==y))
			{
				cout << "Ova grana vec postoji" << endl;
				return;
			}
			novi->susedni = novipom->susedni;
			novipom->susedni = novi;
		}

	//za drugi ne proveravam da li vec ima
	Listasusednosti* novip = new Listasusednosti;
	novip->info = x;
	novip->susedni = nullptr;
	if ((graf[y]->susedni == nullptr) || (graf[y]->susedni->info > x))
	{
		novip->susedni = graf[y]->susedni;
		graf[y]->susedni = novip;
	}
	else {
		Listasusednosti* novipom = graf[y]->susedni;
		while ((novipom->susedni != nullptr) && (novipom->susedni->info < x)) novipom = novipom->susedni;
		novip->susedni = novipom->susedni;
		novipom->susedni = novip;
	}
}

void obrisigranu(int x, int y)
{
	if (dimenzija == -1)
	{
		cout << "Graf jos nije stvore" << endl;
		return;
	}
	

	if (((x >= dimenzija) || (x < 0) || (y >= dimenzija) || (y < 0)) || (graf[x]->info != 1) || (graf[y]->info != 1))
	{
		cout << "Neispravno uneti parametri"<<endl;
		return;
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
	
		while (((novipom->susedni) && (novipom->susedni->info != y))&&!(novipom->susedni->info> y)) novipom = novipom->susedni;
		
		if ((novipom->susedni == nullptr)||(novipom->susedni->info>y))
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

	//brisanje iz druge
	Listasusednosti* pom = graf[y]->susedni;
	if (graf[y]->susedni->info == x)
	{
		graf[y]->susedni = graf[y]->susedni->susedni;
		delete pom;
	}
	else
	{
		while (((pom->susedni) && (pom->susedni->info != x)) && !(pom->susedni->info > x)) pom = pom->susedni;

		if ((pom->susedni == nullptr) || (pom->susedni->info > x))
		{
			cout << "Ova grana ne postoji " << endl;
			return;
		}

		if (pom->susedni->susedni == nullptr)
		{
			Listasusednosti* novip = pom->susedni;
			pom->susedni = nullptr;
			delete novip;
		}
		else
		{
			Listasusednosti* novip = pom->susedni;
			pom->susedni = novip->susedni;
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
	cout << "Graf:"<<endl;
	for (int i = 0; i < dimenzija; i++)
	{
		if (graf[i]->info == 1)
		{
			cout << i;
			Listasusednosti* pom = graf[i]->susedni;
			while (pom)
			{
				cout << "->" << pom->info;
				pom = pom->susedni;
			}
			cout << endl;
		}
	}
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
			dodajcvor();
			break;
		case 3:
			brisanjecvora();
			break;
		case 4:
			dodajgranu();
			break;
		case 5:
			int x, y;
			cout << "Unesi koje cvorove ciju vezu zelis da obrises" << endl;
			cin >> x >> y;
			obrisigranu(x, y);
			break;
		case 6:
			ispis();
			break;
		case 7:
			obrisi();
			break;
		case 8:
			if (dimenzija != -1) obrisi(); //provera da li radi
			return 0;
		}
	}
}