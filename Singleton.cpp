#include <iostream>
#include <cmath>

using namespace std;

class GameManager;

class Character
{
public:
    virtual void attack(Character*) = 0;
    virtual void setHealth(int) = 0;
    virtual int getHealth() = 0;
    virtual int getPosition() = 0;
    virtual void die() = 0;
    virtual void zmienPozycje() = 0;
};

class GameManager // Singleton
{
private:
    static GameManager* instance;
    Character* instanceP;
    Character* instanceE;

    GameManager() 
    {
        instanceP = nullptr;
        instanceE = nullptr;
    }

public:
    static GameManager* getInstance()
    {
        if (instance == nullptr)
        {
            instance = new GameManager();
        }

        return instance;
    }

    void setPlayer(Character* player)
    {
        getInstance()->instanceP = player;
    }

    void setEnemy(Character* enemy)
    {
        getInstance()->instanceE = enemy;
    }

    Character* getPlayer()
    {
        return getInstance()->instanceP;
    }

    Character* getEnemy()
    {
        return getInstance()->instanceE;
    }

    void makeEvent()
    {
        Character* player = getInstance()->instanceP;
        Character* enemy = getInstance()->instanceE;
        if (player != nullptr && enemy != nullptr)
        {
            if (player->getHealth() > 0 && enemy->getHealth() > 0)
            {
                if (abs(player->getPosition() - enemy->getPosition()) < 10)
                {
                    cout << "Gracz i przeciwnik sie spotkali\n";

                    while (player->getHealth() > 0 && enemy->getHealth() > 0)
                    {
                        player->attack(enemy);
                        enemy->attack(player);
                    }
                }
                else
                {
                    cout << "Gracz i przeciwnik sa zbyt daleko\n";
                }
            }
        }
    }
};

GameManager* GameManager::instance = nullptr;

class Player : public Character
{
private:
    int health;
    int position;
    int damage;
    bool attack_;
    bool alive;

public:

    Player(int hp, int pos, int dmg) : Character()
    {
        health = hp;
        position = pos;
        damage = dmg;
        attack_ = false;
        alive = true;
    }

    void attack(Character* enemy)
    {
        if (alive)
        {
            cout << "Gracz zaatakowal przeciwnika zadajac: " << damage << " damage'a\n";
            attack_ = true;
            this->heal();

            enemy->setHealth(enemy->getHealth() - damage);

            if (enemy->getHealth() < 0)
                enemy->die();
        }
    }

    void setHealth(int new_health)
    {
        health = new_health;
    }

    int getHealth()
    {
        return health;
    }

    int getPosition()
    {
        return position;
    }

    void die()
    {
        cout << "Gracz umiera\n";
        alive = false;
    }

    void heal()
    {
        cout << "Gracz sie uleczyl\n";

        if (health <= 95)
            health += 5;
    }

    void zmienPozycje()
    {
        GameManager* manager = GameManager::getInstance();
        if (manager->getPlayer() == nullptr)
            manager->setPlayer(this);

        if (!attack_)
            position += 5;

        manager->makeEvent();
    }
};

class Enemy : public Character
{
private:
    int health;
    int position;
    int damage;
    bool attack_;
    bool alive;
public:

    Enemy(int hp, int pos, int dmg) : Character()
    {
        health = hp;
        position = pos;
        damage = dmg;
        attack_ = false;
        alive = true;
    }

    void attack(Character* player)
    {
        if (alive)
        {
            cout << "Przeciwnik zaatakowal gracza zadajac: " << damage << " damage'a\n";
            attack_ = true;
            player->setHealth(player->getHealth() - damage);
        }
    }

    void setHealth(int new_health)
    {
        health = new_health;
    }

    int getHealth()
    {
        return health;
    }

    int getPosition()
    {
        return position;
    }

    void die()
    {
        cout << "Przeciwnik umiera\n";
        alive = false;
    }

    void zmienPozycje()
    {
        GameManager* manager = GameManager::getInstance();
        if (manager->getEnemy() == nullptr)
            manager->setEnemy(this);

        if (!attack_)
            position -= 5;

        manager->makeEvent();
    }
};

int main()
{
    Character* player = new Player(100, -50, 20);
    Character* enemy = new Enemy(70, 10, 15);

    while (true)
    {
        player->zmienPozycje();
        enemy->zmienPozycje();
    }
}
