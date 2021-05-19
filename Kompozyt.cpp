#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class Zegarek
{
public:
    virtual void pokazGodzine() = 0;
};

class ZegarekKlasyczny : public Zegarek
{
public:
    ZegarekKlasyczny() {}

    void pokazGodzine()
    {
        cout << "Jest godzina 1 AM \n";
    }
};

class ZegarekElektroniczny : public Zegarek
{
public:
    ZegarekElektroniczny() {}

    void pokazGodzine()
    {
        cout << "Jest godzina 13:00\n";
    }
};

class Kompozyt : public Zegarek
{
private:
    vector<Zegarek*> zegarki;

public:
    Kompozyt(vector<Zegarek*> x) 
    {
        zegarki = x;
    }

    void pokazGodzine()
    {
        for (int i = 0; i < zegarki.size(); i++) 
        {
            zegarki[i]->pokazGodzine();
        }
    }

    void dodajZegarek(Zegarek* zegarek)
    {
        zegarki.push_back(zegarek);
    }

    Zegarek* usunZegarek()
    {
        Zegarek* x = zegarki.at(zegarki.size() - 1);
        zegarki.pop_back();
        return x;
    }
};

int main()
{
    Zegarek* a = new ZegarekKlasyczny();
    Zegarek* b = new ZegarekElektroniczny();

    vector<Zegarek*> vec;
    vec.push_back(a);
    vec.push_back(b);

    Zegarek* zegarki = new Kompozyt(vec);

    zegarki->pokazGodzine();

}

