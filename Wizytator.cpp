#include <iostream>
#include <string>

using namespace std;
class WeaponDealer;
class ArmorDealer;

class Player
{
public:
    virtual void visit(WeaponDealer*) = 0;
    virtual void visit(ArmorDealer*) = 0;
    virtual string getName() = 0;
    virtual int getLevel() = 0;
};

class Dealer
{
public:
    virtual void accept(Player*) = 0;
};

class WeaponDealer : public Dealer
{
public:
    WeaponDealer() {}

    void info()
    {
        cout << "Posiadam najlepsze bronie!\n";
    }

    void accept(Player* p)
    {
        cout << "Witaj " << p->getName() << "!\n";
        info();
    }
};

class ArmorDealer : public Dealer
{
public:
    ArmorDealer() {}

    void info()
    {
        cout << "Jesli nic nie kupisz, nie wracaj!\n";
    }

    void accept(Player* p)
    {
        cout << "Witaj " << p->getName() << "!\n";
        if (p->getLevel() < 10)
            cout << "Jesli nie masz levelu 10, nie przychodz\n";
        else
            info();
    }
};

class TPlayer : public Player
{
private:
    string name;
    int level;

public:
    TPlayer(string name, int level)
    {
        this->name = name;
        this->level = level;
    }

    void visit(WeaponDealer* dealer)
    {
        dealer->accept(this);
    }

    void visit(ArmorDealer* dealer)
    {
        dealer->accept(this);
    }

    string getName()
    {
        return name;
    }

    int getLevel()
    {
        return level;
    }
};

int main()
{
    ArmorDealer* d1 = new ArmorDealer();
    WeaponDealer* d2 = new WeaponDealer();

    Player* p = new TPlayer("Eustachy", 9);
    p->visit(d1);
    p->visit(d2);
}