#include <iostream>

using namespace std;

typedef struct Vector2
{
    int x;
    int y;

    Vector2() {}

    Vector2(int a, int b)
    {
        x = a;
        y = b;
    }

}Vector2;

class Pixel
{
private:
    int rgb;
    Vector2 xy;

public:
    Pixel() {}

    Pixel(int rgb, Vector2 xy)
    {
        this->rgb = rgb;
        this->xy = xy;
    }

    void info()
    {
        cout << "To jest pixel o rgb: " << rgb << " i polozeniu: " << xy.x << " " << xy.y << "\n";
    }
};

class PixelIterator
{
public:
    virtual bool hasNext() = 0;
    virtual Pixel* next() = 0;
};

class Image : public PixelIterator
{
private:
    Pixel* pixels;
    int i;
    int n;

public:
    Image(Pixel* pixels, int n)
    {
        this->pixels = pixels;
        this->n = n;
        i = 0;
    }

    bool hasNext()
    {
        return i < n;
    }

    Pixel* next()
    {
        if (hasNext())
        {
            Pixel* p = &pixels[i];
            i++;
            return p;
        }
        else
        {
            i = 0;
        }
    }

};

int main()
{
    Pixel pixels[4];
    pixels[0] = Pixel(312, Vector2(0, 0));
    pixels[1] = Pixel(542, Vector2(1, 0));
    pixels[2] = Pixel(354, Vector2(0, 1));
    pixels[3] = Pixel(132, Vector2(1, 1));

    PixelIterator* i = new Image(pixels, 4);
    while (i->hasNext())
    {
        Pixel* p = i->next();
        p->info();
    }

}
