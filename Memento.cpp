#include <iostream>
#include <string>

using namespace std;

class Memento
{
private:
    string postacGracza;
    string etapGry;

public:
    Memento(string a, string b)
    {
        postacGracza = a;
        etapGry = b;
    }

    string getPostac() { return postacGracza; }

    string getEtap() { return etapGry; }
};

class Rozgrywka
{
private:
    string postacGracza;
    string etapGry;
    int i;
    Memento** mementos;

public:
    Rozgrywka()
    {
        postacGracza = "Zwykly chlop";
        etapGry = "Poziom pierwszy";
        i = 0;
        mementos = new Memento*[10];
    }

    void zapiszGre()
    {


        if (i < 10)
        {
            Memento* zapis = new Memento(postacGracza, etapGry);
            mementos[i] = zapis;
            cout << "Pomyslnie zapisano gre\n";
            cout << postacGracza << ", " << etapGry << "\n";
            i++;
        }
        else
        {
            cout << "Wyczerpano miejsca zapisu gry\n";
        }
    }

    void wczytajGre(int i)
    {
        if (i < 10)
        {
            Memento* wczytaj = mementos[i];
            postacGracza = wczytaj->getPostac();
            etapGry = wczytaj->getEtap();

            cout << "Pomyslnie wczytano zapis: " << i << "\n";
            cout << postacGracza << ", " << etapGry << "\n";
        }
    }

    void przejdzPoziom()
    {
        postacGracza = "Niezwykly chlop";
        etapGry = "Poziom niepierwszy";

        cout << "Pomyslnie przeszedles poziom! Teraz jestes: \n";
        cout << postacGracza << ", " << etapGry << "\n";
    }

    void pokazDane()
    {
        cout << postacGracza << ", " << etapGry << "\n";
    }

};

int main()
{
    Rozgrywka* alegiera = new Rozgrywka();
    alegiera->pokazDane();
    alegiera->zapiszGre();
    alegiera->przejdzPoziom();
    alegiera->wczytajGre(0);
}
