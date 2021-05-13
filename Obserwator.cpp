#include <iostream>
#include <string>
class Obserwator;
class Obserwowany;

using namespace std;

class Obserwator
{
public:
    virtual void aktualizacjaDanych(Obserwowany*) = 0;
};

class Obserwowany
{
public:
    virtual void dodajObserwatora(Obserwator*) = 0;
    virtual void usunObserwatora(int) = 0;
    virtual void zaaktualizujStatus() = 0;
    virtual float podajPolozenie() = 0;
    virtual void zmienPolozenie()  = 0;
};

class Klient : public Obserwator
{
private:
    string zamowienie;
    bool zrealizowane;
    float adres;

public:
    Klient(string zamowienie, float adres) : Obserwator()
    {
        this->zamowienie = zamowienie;
        this->adres = adres;
        zrealizowane = false;
    }

    void aktualizacjaDanych(Obserwowany* obserwowany)
    {
        if (!zrealizowane)
        {
            if (adres > obserwowany->podajPolozenie())
            {
                cout << "Kurier jest prawie u celu\n";
                cout << "zrealizowano zamówienie: " << zamowienie << '\n';
                zrealizowane = true;
            }
            else
            {
                cout << "Kurier jest jeszcze daleko\n";
            }
        }
    }
};

class Kurier : public Obserwowany
{
private:
    float polozenie;
    Obserwator** obserwatorzy;
    int id;

public:
    Kurier(float polozenie, int n) : Obserwowany()
    {
        this->polozenie = polozenie;
        this->id = 0;

        obserwatorzy = new Obserwator * [n];
    }

    void dodajObserwatora(Obserwator* nowy)
    {
        obserwatorzy[id] = nowy;
        id++;
    }

    void usunObserwatora(int i)
    {
        Obserwator* temp = obserwatorzy[i];
        obserwatorzy[i] = nullptr;
        delete temp;
    }

    void zaaktualizujStatus()
    {
        for (int i = 0; i < id; i++)
        {
            if (obserwatorzy[i] != nullptr)
                obserwatorzy[i]->aktualizacjaDanych(this);
        }
    }

    float podajPolozenie()
    {
        return polozenie;
    }

    void zmienPolozenie()
    {
        if (polozenie > 19)
        {
            polozenie -= 20;
        }
    }
};

int main()
{
    Obserwator* a = new Klient("Paczka jakas", 30.0);
    Obserwator* b = new Klient("Buty", 60.0);
    Obserwator* c = new Klient("Bananowy Iphone", 45.0);
    Obserwowany*  d = new Kurier(260.0, 5);

    d->dodajObserwatora(a);
    d->dodajObserwatora(b);
    d->dodajObserwatora(c);

    while (d->podajPolozenie() > 20)
    {
        d->zaaktualizujStatus();
        d->zmienPolozenie();
    }
}

