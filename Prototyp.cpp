#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Stormtrooper;

class Prototyp
{
public:
    virtual Stormtrooper* klonuj() = 0;
    virtual void execute() = 0;
};

class Stormtrooper : public Prototyp
{
private:
    int id;
    float wysokosc;
    string bron;

public:
    Stormtrooper() {}

    Stormtrooper(int id, float wysokosc, string bron)
    {
        this->id = id;
        this->wysokosc = wysokosc;
        this->bron = bron;
    }

    void execute()
    {
        cout << "execute order 66\n";
        int x = rand() % 100;
        cout << "klon warstwy: " << id << " zabil: " << x << " Jedi\n";
    }

    Stormtrooper* klonuj()
    {
        return new Stormtrooper(id + 1, wysokosc, bron);
    }
};

int main()
{
    srand(time(NULL));
    Prototyp* pierwszy = new Stormtrooper(0, 1.8, "karabinek");
    Prototyp* drugi = pierwszy->klonuj();
    pierwszy->execute();
    drugi->execute();
}

