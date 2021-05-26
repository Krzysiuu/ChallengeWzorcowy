#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

class Strategy
{
public:
    virtual void executeStrategy() = 0;
    virtual void attack() = 0;
    virtual void gatherUnits() = 0;
};

class Defensive : public Strategy
{
private:
    int minUnits;
    int heroes;
    int currentUnits;
    int currentHeroes;

    void buildWalls()
    {
        cout << "Zbudowano mur obronny\n";
    }

public:
    Defensive(int units, int heroes)
    {
        minUnits = units;
        this->heroes = heroes;
        currentUnits = 0;
        currentHeroes = 0;
    }

    void gatherUnits()
    {
        currentUnits += 30;

        if (currentHeroes < heroes)
            currentHeroes++;
    }

    void attack()
    {
        bool condition = currentUnits > minUnits;
        if (condition)
            cout << "Zaatakowano gracza cala armia: "<< currentUnits <<" jednostek\n";
        else
        {
            while (condition)
            {
                cout << "Armia jest za mala do ataku\n";
                gatherUnits();
            }

            attack();
        }
    }

    void executeStrategy()
    {
        buildWalls();
        gatherUnits();
        attack();
    }

};

class Default : public Strategy
{
private:
    string mainHero;
    int army;
    int hero;

    void getHero(string name)
    {
        if (name == mainHero)
        {
            hero++;
            cout << "Dodano glownego bohatera: "<< mainHero <<"\n";
        }
        else
        {
            cout << "To nie jest glowny bohater\n";
        }
    }

public:
    Default(string hero)
    {
        army = 0;
        this->hero = 0;
        mainHero = hero;
    }

    void gatherUnits()
    {
        army += 30;
    }

    void attack()
    {
        if (hero == 0)
            cout << "Zaatakowano gracza armia\n";
        else
            cout << "Zaatakowano gracza armia: "<< army << " jednostek, z bohaterem: " << mainHero << "\n";
    }

    void executeStrategy()
    {
        getHero(mainHero);
        gatherUnits();
        attack();
    }
};

class Agressive : public Strategy
{
private:
    int units;

    void takeTerritory()
    {
        cout << "Zajeto wiecej terytorium\n";
    }

public:
    Agressive()
    {
        units = 0;
    }

    void gatherUnits()
    {
        units += 60;
    }

    void attack()
    {
        cout << "Dodano bonusowe jednostki\n";
        gatherUnits();
        cout << "Zaatakowano gracza armia: "<< units << " jednostek\n";
    }

    void executeStrategy()
    {
        gatherUnits();
        takeTerritory();
        attack();
    }
};

class EnemyAI
{
private:
    Strategy** strategies;
    Strategy* currentStrategy;

public:
    EnemyAI()
    {
        strategies = new Strategy*[3];
        strategies[0] = new Defensive(90, 3);
        strategies[1] = new Default("Gandalf");
        strategies[2] = new Agressive();
    }

    void chooseStrategy()
    {
        int strategy = rand() % 3;
        currentStrategy = strategies[strategy];
        currentStrategy->executeStrategy();
    }
};

int main()
{
    srand(time(NULL));
    EnemyAI* enemy = new EnemyAI();
    enemy->chooseStrategy();
}

