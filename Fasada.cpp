#include <iostream>
#include <vector>

using namespace std;

class Neuron
{
private:
	int id;
	int wejscia;
	vector<float> wagi;

public:
	Neuron(int id, int wejscia)
	{
		this->id = id;
		this->wejscia = wejscia;

			for (int i = 0; i < wejscia; i++)
			{
				wagi.push_back(1);
			}
	}

	void ucz()
	{
		cout << "Neuron " << id << " sie uczy\n";
	}

	void przewiduj()
	{
		cout << "Neuron " << id << " przewiduje wynik\n";
	}
};

class ZbiorTreningowy
{
private:
	vector<float> zbiorX;
	vector<float> zbiorY;

public:
	ZbiorTreningowy(float* tabX, float* tabY, int n)
	{
		for (int i = 0; i < n; i++)
		{
			zbiorX.push_back(tabX[i]);
			zbiorY.push_back(tabY[i]);
		}
	}

	vector<float> getX()
	{
		return zbiorX;
	}

	vector<float> getY()
	{
		return zbiorY;
	}
};

class SiecNeuronowa
{
private:
	vector<Neuron> neurony;
	int liczba;
	float precyzja;
	float odwolanie;
	float skutecznosc;

public:
	SiecNeuronowa(int liczba, int wejsciaN)
	{
		precyzja = 0.0;
		odwolanie = 0.0;
		skutecznosc = 0.0;
		this->liczba = liczba;
		for (int i = 0; i < liczba; i++)
		{
			neurony.push_back(Neuron(i, wejsciaN));
		}
	}

	void uczSiec(ZbiorTreningowy* zbiorTrain)
	{
		cout << "Siec sie uczy: \n";

		for (int i = 0; i < liczba; i++)
		{
			neurony[i].ucz();
		}
	}

	void pokazWskazniki()
	{
		cout << "Precyzja: " << precyzja << "\n" << "Odwolanie: " << odwolanie << "\n" << "Skutecznosc: " << skutecznosc << "\n";
	}

	void testujSiec(ZbiorTreningowy* zbiorTest)
	{
		cout << "Testujemy siec \n";

		//randomowe wartości
		precyzja = 0.6;
		odwolanie = 0.4;
		skutecznosc = 0.8;
	}
};

class Fasada
{
private:
	SiecNeuronowa* siec;
	ZbiorTreningowy* trening;
	ZbiorTreningowy* test;
	float wynik;

public:
	Fasada(int n, int w)
	{
		siec = new SiecNeuronowa(n, w);
		trening = nullptr;
		test = nullptr;
	}

	void nauczSiec(float* daneX, float* daneY, int n)
	{
		//tu by nastąpiło podzielenie danych ale mi się nie chce
		trening = new ZbiorTreningowy(daneX, daneY, n);
		test = new ZbiorTreningowy(daneX, daneY, n);
		siec->uczSiec(trening);
		siec->testujSiec(test);
	}

	void PodajWynik()
	{
		siec->pokazWskazniki();
		wynik = 1.0;
	}
};

class Klient
{
private:

public:
	Klient() {}

	void Sprawdz(Fasada* x, float* daneUczenia, int n, float* przyklad)
	{
		x->nauczSiec(daneUczenia, daneUczenia, n);
		x->PodajWynik();
	}
};

int main()
{
	Klient k = Klient();
	
	Fasada* fasada = new Fasada(5, 3);
	float dane[] = {0.0, 1.0};
	
	k.Sprawdz(fasada, dane,2, dane);
}
