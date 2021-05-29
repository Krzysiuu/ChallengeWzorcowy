#include <iostream>
#include <string>

using namespace std;

class ModelML
{
protected:
    float* daneX;
    float* odpowiedziY;
    string model;

public:
    ModelML(float* daneX)
    {
        this->daneX = daneX;
        odpowiedziY = nullptr;
        model = "";
    }

    void nauczMaszyne()
    {
        stworzModel();
        dokonajObliczen();

        for (int i = 0; i < 10; i++)
        {
            cout << odpowiedziY[i] << "\n";
        }
    }

    virtual void stworzModel() = 0;
    virtual void dokonajObliczen() = 0;

};

class SiecNeuronowa : public ModelML
{
public:
    SiecNeuronowa(float* daneX) : ModelML(daneX) {}
    void stworzModel()
    {
        cout << "Stworzono model sieci neuronowej\n";
        ModelML::model = "Siec Neuronowa";
    }

    void dokonajObliczen()
    {
        cout << "Siec neuronowa nauczyla sie zbioru X\n";
        ModelML::odpowiedziY = new float[10];
        for (int i = 0; i < 10; i++)
        {
            odpowiedziY[i] = 1;
        }
    }
};

class DrzewoDecyzyjne : public ModelML
{
public:
    DrzewoDecyzyjne(float* daneX) : ModelML(daneX) {}
    void stworzModel()
    {
        cout << "Stworzono model drzewa decyzyjnego\n";
        ModelML::model = "Drzewo decyzyjne";
    }

    void dokonajObliczen()
    {
        cout << "Drzewo nauczylo sie zbioru X\n";
        ModelML::odpowiedziY = new float[10];
        for (int i = 0; i < 10; i++)
        {
            odpowiedziY[i] = 0;
        }
    }
};

int main()
{
    float* daneX = new float[10];
    ModelML* x = new DrzewoDecyzyjne(daneX);
    x->nauczMaszyne();

    ModelML* y = new SiecNeuronowa(daneX);
    y->nauczMaszyne();
}
