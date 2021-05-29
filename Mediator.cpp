#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Obliczenia;
class Wykres;

class Mediator
{
private:
    Obliczenia* obliczenia;
    Wykres* wykres;

public:
    Mediator() {}

    void setMediatorA(Obliczenia* a)
    {
        obliczenia = a;
    }

    void setMediatorB(Wykres* b)
    {
        wykres = b;
    }

    void wyslijDoWykresu(float* argumenty, float* wyniki, int n, string funkcja)
    {
        wykres->setZbiorX(argumenty);
        wykres->setZbiorY(wyniki);
        wykres->setSize(n);
        wykres->wyswietl(funkcja);
    }
};

class Obliczenia
{
private:
    float* argumenty;
    float* wyniki;
    Mediator* mediator;
    int n;
    string funkcja;

    void wyslij()
    {
        mediator->wyslijDoWykresu(argumenty, wyniki, n, funkcja);
    }

public:
    Obliczenia(float* argumenty, Mediator* mediator, int n)
    {
        this->argumenty = argumenty;
        this->mediator = mediator;
        this->n = n;
        wyniki = new float[n];
        mediator->setMediatorA(this);
    }

    void oblicz(string funckja)
    {
        if (funckja == "pierwiastek")
        {
            this->funkcja = funkcja;
            for (int i = 0; i < n; i++)
            {
                wyniki[i] = sqrt(argumenty[i]);
            }

            wyslij();
        }
    }

};

class Wykres
{
private:
    float* zbiorX;
    float* zbiorY;
    int n;
    Mediator* mediator;

public:
    Wykres(Mediator* mediator)
    {
        this->mediator = mediator;
    }

    void setZbiorX(float* x) { zbiorX = x; }
    void setZbiorY(float* y) { zbiorY = y; }
    void setSize(int n) { this->n = n; }

    void wyswietl(string funkcja)
    {
        cout << "rysuje funkcje: " << funkcja << "dla argumentow i wartosci: \n";
        for (int i = 0; i < n; i++)
        {
            cout << zbiorX[i] << " : " << zbiorY << "\n";
        }
    }
};


int main()
{
    float* x = new float[5];
    x[0] = 0.5;
    x[1] = 2.0;
    x[2] = 4.0;
    x[3] = 16.0;
    x[4] = 24.0;

    Mediator* mediator = new Mediator();

    Obliczenia* oblicz = new Obliczenia(x, mediator, 5);
    Wykres* wykres = new Wykres(mediator);

    oblicz->oblicz("pierwiastek");
}