#include <iostream>
#include <string>

using namespace std;

class Plik
{
private:
    float rozmiar;
    string nazwa;

public:
    Plik() {}

    Plik(float rozmiar, string nazwa)
    {
        this->rozmiar = rozmiar;
        this->nazwa = nazwa;
    }

    float Rozmiar()
    {
        return rozmiar;
    }
};

class IArchiwum
{
public:
    virtual void zapiszPliki(Plik* pliki, int n) = 0;
};

class Archiwum : public IArchiwum
{
private:
    float rozmiar;
    string typ_kompresji;
    Plik* pliki;
    int n;

public:
    Archiwum()
    {
        rozmiar = 0;
        typ_kompresji = "";
        pliki = nullptr;
        n = 0;
    }

    void zapiszPliki(Plik* pliki, int n)
    {
        this->n = n;
        this->pliki = pliki;

        for (int i = 0; i < n; i++)
        {
            rozmiar += this->pliki[i].Rozmiar();
        }

        cout << "Zapisano pliki\n";
    }

    void Kompresuj(string typ_kompresji)
    {
        this->typ_kompresji = typ_kompresji;
        if (typ_kompresji == "rar")
        {
            rozmiar /= 2;
            cout << "Zapisano jako rar\n";
        }
        else if (typ_kompresji == "zip")
        {
            rozmiar /= 2.5;
            cout << "Zapisano jako zip\n";
        }
    }

    float Rozmiar()
    {
        return rozmiar;
    }
};

class Proxy : public IArchiwum
{
private:
    Archiwum* archiwum;

public:
    Proxy(Archiwum* archiwum)
    {
        this->archiwum = archiwum;
    }

    void zapiszPliki(Plik* pliki, int n)
    {
        archiwum->zapiszPliki(pliki, n);

        if (archiwum->Rozmiar() > 2048.0)
        {
            archiwum->Kompresuj("zip");
        }
        else if (archiwum->Rozmiar() > 1024.0)
        {
            archiwum->Kompresuj("rar");
        }
    }
};

int main()
{
    Plik pliki[3];
    pliki[0] = Plik(212.21, "Xd.txt");
    pliki[1] = Plik(425.4, "XD.txt");
    pliki[2] = Plik(1242.9, "XDDD.txt");
    Archiwum* achiwumzX = new Archiwum();
    IArchiwum* x = new Proxy(achiwumzX);
    x->zapiszPliki(pliki, 3);
}
