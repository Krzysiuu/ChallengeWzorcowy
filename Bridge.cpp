#include <iostream>
#include <string>

using namespace std;

typedef struct Vector3
{
    float x;
    float y;
    float z;

    Vector3(float x, float y, float z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

}Vector3;

class Textura
{
public:
    virtual void ustawTexture() = 0;
};

class Metal : public Textura
{
private:
    float polysk;

public:
    Metal(float x)
    {
        polysk = x;

        if (polysk > 1)
        {
            polysk = 1.0f;
        }
        else if (polysk < 0)
        {
            polysk = 0.0f;
        }

    }

    void ustawTexture()
    {
        string s = "Ustawiono metal: ";

        if (polysk > 0.7)
        {
            s += "bardzo ";
        }
        else if (polysk > 0.4)
        {
            s += "srednio ";
        }
        else
        {
            s += "slabo ";
        }

        s += "blyszczacy\n";

        cout << s;
    }
};

class Drewno : public Textura
{
private:
    float chropowatosc;

public:
    Drewno(float x)
    {
        chropowatosc = x;

        if (chropowatosc > 1)
        {
            chropowatosc = 1.0f;
        }
        else if (chropowatosc < 0)
        {
            chropowatosc = 0.0f;
        }

    }

    void ustawTexture()
    {
        string s = "Ustawiono drewno: ";
        
        if (chropowatosc > 0.5f)
        {
            s += "chropowate\n";
        }
        else
        {
            s += "gladkie\n";
        }

        cout << s;
    }
};

class Obiekt3D
{
private:
    Textura* textura;

public:
    Obiekt3D(Textura* textura) { this->textura = textura; }
    void pokazTexture() { textura->ustawTexture(); }
    virtual void umiesc(Vector3) = 0;

};

class Kula : public Obiekt3D
{
private:
    float promien;

public:
    Kula(Textura* textura, float r) : Obiekt3D(textura)
    {
        promien = r;
    }

    void umiesc(Vector3 vec)
    {
        cout << "Umieszczono Kule w pozycjach x, y, z:\n";
        cout << vec.x << " " << vec.y << " " << vec.z << "\n";
        cout << "O promieniu: " << promien << "\n";
        Obiekt3D::pokazTexture();
    }
};

int main()
{
    Obiekt3D* kula = new Kula(new Metal(0.1f), 5.0f);
    kula->umiesc(Vector3(0.0f, 0.0f, 0.0f));

    Obiekt3D* kula2 = new Kula(new Drewno(0.6f), 1.0f);
    kula2->umiesc(Vector3(0.6f, 0.0f, 1.0f));
}