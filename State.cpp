#include <iostream>
#include <string>

using namespace std;
class Player;

class State
{
public:
    virtual void handle(Player*) = 0;
};

class Player
{
private:
    State** states;
    float speed;
    string activeAnimation;

public:
    Player(State** states)
    {
        this->states = states;
        speed = 3.0f;
        activeAnimation = "";
    }

    void request(string state)
    {
        if (state == "Walking")
        {
            states[0]->handle(this);
        }
        else if (state == "Running")
        {
            states[1]->handle(this);
        }
    }

    void info()
    {
        cout << "Gracz porusza sie z predkoscia: " << speed << "\n";
        cout << "Odgrywana jest animacja: " << activeAnimation << "\n";
    }

    void setSpeed(float speed)
    {
        this->speed = speed;
    }

    void setAnimation(string animation)
    {
        activeAnimation = animation;
    }
};


class Walking : public State
{
private:
    string animation;

public:
    Walking() { animation = "Walking"; }

    void handle(Player* player)
    {
        player->setAnimation(animation);
        player->setSpeed(3.0f);
    }
};

class Running : public State
{
private:
    string animation;

public:
    Running() { animation = "Running"; }

    void handle(Player* player)
    {
        player->setAnimation(animation);
        player->setSpeed(6.0f);
    }
};

int main()
{
    State** states = new State * [2];
    states[0] = new Walking();
    states[1] = new Running();

    Player* p = new Player(states);

    p->request("Walking");
    p->info();
    p->request("Running");
    p->info();
}