#include <iostream>

using namespace std;

class Aparat
{
public:
    virtual void zrobZdjecie() = 0;
};

class AparatFotograficzny : public Aparat
{
public:
    AparatFotograficzny() {}
    void zrobZdjecie()
    {
        cout << "Aparat robi zdjecie\n";
    }
};

class Dekorator : public Aparat
{
public:
    virtual void zrobZdjecie() = 0;
    virtual void dekorujAparat(Aparat*) = 0;
};

class DekoratorFiltr : public Dekorator
{
private:
    Aparat* aparat;
    int* filtry;

public:
    DekoratorFiltr(int* filtry)
    {
        this->filtry = filtry;
        aparat = new AparatFotograficzny();
    }

    void dekorujAparat(Aparat* aparat)
    {
        this->aparat = aparat;
    }

    void dodajFiltr()
    {
        cout << "Dodano filtr do zdjecia \n";
    }

    void zrobZdjecie()
    {
        dodajFiltr();
        aparat->zrobZdjecie();
    }
};

class DekoratorPrzeksztalcen : public Dekorator
{
private:
    Aparat* aparat;
    int* przeksztalcenia;

public:
    DekoratorPrzeksztalcen(int* przeksztalcenia)
    {
        this->przeksztalcenia = przeksztalcenia;
        aparat = new AparatFotograficzny();
    }

    void dekorujAparat(Aparat* aparat)
    {
        this->aparat = aparat;
    }

    void dokonajPrzeksztalcenia()
    {
        cout << "Dokonano przeksztalcenia zdjecia \n";
    }

    void zrobZdjecie()
    {
        aparat->zrobZdjecie();
        dokonajPrzeksztalcenia();
    }
};

int main()
{
    cout << "Aparat bez dekoracji\n";
    Aparat* x = new AparatFotograficzny();
    x->zrobZdjecie();

    cout << "Aparat udekorowany:\n";
    int* filtry = new int[10];
    Aparat* y = new DekoratorFiltr(filtry);

    y->zrobZdjecie();

}

