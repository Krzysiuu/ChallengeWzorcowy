#include <iostream>

using namespace std;

class Kanapa
{
public:
    virtual void info() = 0;
};

class Stolik
{
public:
    virtual void info() = 0;
};

class FabrykaAbstrakcyjna
{
public:
    virtual Kanapa* stworzKanape() = 0;
    virtual Stolik* stworzStolik() = 0;
};

class KanapaStaromodna : public Kanapa
{
public:
    void info()
    {
        cout << "To jest kanapa staromodna\n";
    }
};

class KanapaNowoczesna : public Kanapa
{
public:
    void info()
    {
        cout << "To jest kanapa nowoczesna\n";
    }
};

class StolikStaromodny : public Stolik
{
public:
    void info()
    {
        cout << "To jest stolik staromodny\n";
    }
};

class StolikNowoczesny : public Stolik
{
public:
    void info()
    {
        cout << "To jest stolik nowoczesny\n";
    }
};

class MebleStaromodne : public FabrykaAbstrakcyjna
{
public:
    MebleStaromodne() {}

    Kanapa* stworzKanape()
    {
        cout << "Stworzono kanape staromodna\n";
        return new KanapaStaromodna();
    }

    Stolik* stworzStolik()        
    {
        cout << "Stworzono stolik staromodny\n";
        return new StolikStaromodny();
    }
};

class MebleNowoczesne : public FabrykaAbstrakcyjna
{
public:
    MebleNowoczesne() {}

    Kanapa* stworzKanape()
    {
        cout << "Stworzono kanape nowoczesna\n";
        return new KanapaNowoczesna();
    }

    Stolik* stworzStolik()
    {
        cout << "Stworzono stolik nowoczesny\n";
        return new StolikNowoczesny();
    }
};


int main()
{
    FabrykaAbstrakcyjna* Staromodna = new MebleStaromodne();
    FabrykaAbstrakcyjna* Nowoczesna = new MebleNowoczesne();

    Kanapa* x = Nowoczesna->stworzKanape();
    x->info();

    Stolik* y = Staromodna->stworzStolik();
    y->info();
}
