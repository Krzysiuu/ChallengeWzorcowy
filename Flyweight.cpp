#include <iostream>
#include <string>
#include <vector>

using namespace std;

typedef struct Vector3
{
    float x;
    float y;
    float z;

    Vector3() {}

    Vector3(float posX, float posY, float posZ)
    {
        x = posX;
        y = posY;
        z = posZ;
    }
}Vector3;

class EnemyType
{
private:
    string name;
    string model;
    int damage;
    int health;

public:
    EnemyType(string name, string model, int damage, int health)
    {
        this->name = name;
        this->model = model;
        this->damage = damage;
        this->health = health;
    }

    string getName()
    {
        return name;
    }

    int getDamage()
    {
        return damage;
    }
};

class Enemy
{
private:
    Vector3 position;
    EnemyType* type;

public:
    Enemy(Vector3 pos, EnemyType* type)
    {
        position = pos;
        this->type = type;
    }

    void move()
    {
        cout << "Nowa pozycja przeciwnika: ";
        position.x *= 2;
        position.y *= 2;
        position.z *= 2;
        cout << position.x << " " << position.y << " " << position.z << "\n";
    }

    void attack()
    {
        cout << "Zaatakowano gracza zadajac: " << type->getDamage() << " damage'a\n";
    }
};

class EnemyFactory
{
private:
    vector<EnemyType*> enemyTypes;

public:
    EnemyFactory() {}

    EnemyType* getEnemyType(string name, string model, int damage, int health)
    {
        for (int i = 0; i < enemyTypes.size(); i++)
        {
            if (enemyTypes[i]->getName() == name)
                return enemyTypes[i];
        }
        EnemyType* type = new EnemyType(name, model, damage, health);
        enemyTypes.push_back(type);
        return type;
    }
};

class Map
{
private:
    vector<Enemy*> enemies;
    EnemyFactory* factory;
public:
    Map() { factory = new EnemyFactory(); }

    void spawnEnemy(string name, string model, int damage, int health, Vector3 position)
    {
        EnemyType* enemy = factory->getEnemyType(name, model, damage, health);
        enemies.push_back(new Enemy(position, enemy));
    }

    void moveEnemies()
    {
        for (int i = 0; i < enemies.size(); i++)
        {
            enemies[i]->move();
            enemies[i]->attack();
        }
    }
};

int main()
{
    Map* m = new Map();
    m->spawnEnemy("Combine", "CombineModel", 10, 100, Vector3(0.0, 0.0, 0.0));
    m->spawnEnemy("Zombie", "ZombieModel", 20, 100, Vector3(1.0, 2.0, 3.0));
    m->moveEnemies();
}