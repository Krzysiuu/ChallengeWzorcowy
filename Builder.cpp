#include <iostream>

using namespace std;

class MLBuilder
{
public:
    virtual void preprocessData(float* data, int n) = 0;
    virtual void makeModel() = 0;
    virtual void fitData() = 0;
};

class KMeans : public MLBuilder
{
private:
    float* data;
    int n;

public:
    KMeans() {}

    void preprocessData(float* data, int n)
    {
        this->data = data;
        this->n = n;
        cout << "Przetworzono i przygotowano dane do modelu K-means\n";
    }

    void makeModel()
    {
        cout << "Stworzono model K-means\n";
    }

    void fitData()
    {
        cout << "Nauczono model danymi: \n";
        for (int i = 0; i < n; i++)
        {
            cout << data[i] << " ";
        }
        cout << "\n";
    }
};

class RandomForest : public MLBuilder
{
private:
    float* data;
    int n;

public:
    RandomForest() {}

    void preprocessData(float* data, int n)
    {
        this->data = data;
        this->n = n;
        cout << "Przetworzono i przygotowano dane do modelu RandomForest\n";
    }

    void makeModel()
    {
        cout << "Stworzono model RandomForest\n";
    }

    void fitData()
    {
        cout << "Nauczono model danymi: \n";
        for (int i = 0; i < n; i++)
        {
            cout << data[i] << " ";
        }
        cout << "\n";
    }
};

class Director
{
private:
    MLBuilder* builder;

public:
    Director(MLBuilder* builder)
    {
        this->builder = builder;
    }

    void construct(float* data, int n)
    {
        builder->preprocessData(data, n);
        builder->makeModel();
        builder->fitData();
    }
};

int main()
{
    MLBuilder* b = new KMeans();
    MLBuilder* a = new RandomForest();

    float* x = new float[3];
    x[0] = 0.1f;
    x[1] = 1.6f;
    x[2] = 2.0f;

    Director* xd = new Director(b);
    Director* xdd = new Director(a);

    xd->construct(x, 3);
    xdd->construct(x, 3);
}