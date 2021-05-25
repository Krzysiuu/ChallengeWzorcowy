#include <iostream>
#include <string>
#include <queue>
#include <ctime>
#include <cstdlib>

using namespace std;

class Kawa
{
private:
    float rozmiar;
    string ziarno;
    bool mleko;

public:
    Kawa()
    {
        rozmiar = NULL;
        ziarno = "";
        mleko = false;
    }

    void info()
    {
        if (mleko)
        {
            cout << "Jest to kawa " << ziarno << ", z mlekiem,  o rozmiarze " << rozmiar << "\n";
        }
        else
        {
            cout << "Jest to kawa " << ziarno << ", o rozmiarze " << rozmiar << "\n";
        }
    }

    void ustawZiarno(string ziarno)
    {
        this->ziarno = ziarno;
    }

    void ustawRozmiar(float rozmiar)
    {
        this->rozmiar = rozmiar;
    }

    void ustawMleko()
    {
        mleko = true;
    }
};

class Command
{
public:
    virtual Kawa* wykonaj(Kawa*) = 0;
};

class MlynekDoZiarna : public Command
{
private:
    string rodzajZiarna;
    float doZmielenia;

public:
    MlynekDoZiarna(string ziarno, float ilosc)
    {
        rodzajZiarna = ziarno;
        doZmielenia = ilosc;
    }

    Kawa* wykonaj(Kawa* kawa)
    {
        kawa->ustawRozmiar(doZmielenia);
        kawa->ustawZiarno(rodzajZiarna);
        return kawa;
    }
};

class DozownikMleka : public Command
{
private:
    float iloscMleka;

public:
    DozownikMleka(float ilosc)
    {
        iloscMleka = ilosc;
    }
    
    Kawa* wykonaj(Kawa* kawa)
    {
        if (iloscMleka < 5.0f)
        {
            cout << "Za malo mleka\n";
        }
        else
        {
            kawa->ustawMleko();
            iloscMleka -= 5.0f;
        }

        return kawa;
    }
};

class EkspresDoKawy
{
private:
    queue<Command*> polecenia;

    void wykonajPolecenia(Kawa* kawusia)
    {
        while (!polecenia.empty())
        {
            Command* polecenie = polecenia.front();
            polecenia.pop();
            polecenie->wykonaj(kawusia);
            delete polecenie;
        }
    }

public:

    EkspresDoKawy() {}

    Kawa* stworzKawe(string ziarno, bool mleko, float ilosc)
    {
        Kawa* kawusia = new Kawa();
        Command* polecenie1 = new MlynekDoZiarna(ziarno, ilosc);
        polecenia.push(polecenie1);
        if (mleko)
        {
            Command* polecenie2 = new DozownikMleka((rand() % 100) * 0.1f);
            polecenia.push(polecenie2);
        }

        wykonajPolecenia(kawusia);
        return kawusia;
    }

};

int main()
{
    srand(time(NULL));
    EkspresDoKawy* ekspresik = new EkspresDoKawy();
    Kawa* kawusia = ekspresik->stworzKawe("Arabica", true, 200.0);
    kawusia->info();
}
