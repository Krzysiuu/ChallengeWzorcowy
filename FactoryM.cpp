#include <iostream>

using namespace std;

class Spawner;
class Mob;
class SpawnerSmoka;
class SpawnerWilka;
class Wilk;
class Smok;
class Lokacja;

typedef struct Vector2
{
    int x;
    int y;

    Vector2() {}

    Vector2(int x1, int y1)
    {
        x = x1;
        y = y1;
    }

}Vector2;

class Mob
{
public:
    Mob() {}
    virtual void wedrujPoMapie() { cout << "Mob biega po mapie\n"; }
};

class Wilk : public Mob
{
private:
    Vector2 polozenie;
public:
    Wilk(Vector2 polozenie) : Mob() { this->polozenie = polozenie; }

    void wedrujPoMapie()
    {
        polozenie.x += 5;
        polozenie.y += 5;

        cout << "Wilk biega po mapie\n";
    }
};

class Smok : public Mob
{
private:
    Vector2 polozenie;
public:
    Smok(Vector2 polozenie) : Mob() { this->polozenie = polozenie; }

    void wedrujPoMapie()
    {
        polozenie.x += 20;
        polozenie.y += 20;

        cout << "Smok lata po mapie\n";
    }
};

class Spawner
{
public:
    virtual Mob* stworzMoba() { return new Mob(); }
    virtual void zatrzymajSpawn() {};
    virtual void wznowSpawn() {};
};

class Lokacja
{
private:
    Spawner** spawnery;
    int n;

public:
    Lokacja(int n, Spawner** spawnery)
    {
        this->n = n;
        this->spawnery = spawnery;

        zaladujLokacje();
    }

    void zaladujLokacje()
    {
        cout << "Gracz wszedl do nowej lokacji\n";
    }

    Mob* stworzMobaX(int i)
    {
        return spawnery[i]->stworzMoba();
    }
};

class SpawnerWilka : public Spawner
{
private:
    bool czyTworzyc;
    Vector2 polozenie;
public:
    SpawnerWilka(Vector2 polozenie)
    {
        this->czyTworzyc = true;
        this->polozenie = polozenie;
    }

    Mob* stworzMoba()
    {
        if (czyTworzyc)
        {
            cout << "Stworzono moba: Wilk\n";
            return new Wilk(polozenie);
        }
        else
        {
            cout << "Tworzenie Wilka zablokowane\n";
        }
    }

    void zatrzymajSpawn()
    {
        czyTworzyc = false;
    }

    void wznowSpawn()
    {
        czyTworzyc = true;
    }
};

class SpawnerSmoka : public Spawner
{
private:
    bool czyTworzyc;
    Vector2 polozenie;
    int maximum;
    int counter;
public:
    SpawnerSmoka(int maximum, Vector2 polozenie)
    {
        this->maximum = maximum;
        this->polozenie = polozenie;
        counter = 0;
        czyTworzyc = true;
    }

    Mob* stworzMoba()
    {
        if (czyTworzyc && counter < maximum)
        {
            cout << "Stworzono moba: Smok\n";
            counter++;
            return new Smok(polozenie);
        }
        else
        {
            cout << "Tworzenie Smoka zablokowane\n";
        }
    }

    void zatrzymajSpawn()
    {
        czyTworzyc = false;
    }

    void wznowSpawn()
    {
        czyTworzyc = true;
    }
};

int main()
{
    Spawner** spawnery = new Spawner *[2];
    spawnery[0] = new SpawnerWilka(Vector2(1, 2));
    spawnery[1] = new SpawnerSmoka(4, Vector2(-5, -10));

    Lokacja x = Lokacja(2, spawnery);
    Mob* wilk = x.stworzMobaX(0);
    Mob* smok = x.stworzMobaX(1);

    wilk->wedrujPoMapie();
    smok->wedrujPoMapie();

    spawnery[0]->zatrzymajSpawn();
    Mob* wilk2 = x.stworzMobaX(0);
}

