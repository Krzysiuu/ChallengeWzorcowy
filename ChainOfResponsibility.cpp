#include <iostream>
#include <string>

using namespace std;

class Request
{
private:
    string text;
    int correctionExtent;

public:
    Request(string text, int correctionExtent)
    {
        this->text = text;
        this->correctionExtent = correctionExtent;
    }

    string getText()
    {
        return text;
    }

    int getExtent()
    {
        return correctionExtent;
    }

    void setText(string newText)
    {
        text = newText;
    }
};

class Handler
{
public:
    virtual Request* handle(Request*) = 0;
};

class CharCorrection : public Handler
{
private:
    Handler* next;

public:
    CharCorrection(Handler* next)
    {
        this->next = next;
    }

    Request* handle(Request* r)
    {
        if ((r->getExtent() & 1) == 1)
        {
            string corrected = r->getText();
            char temp = corrected[0];
            temp -= 32;
            corrected[0] = temp;
            r->setText(corrected);
        }
 
        if (next != nullptr)
        {
            r = next->handle(r);
        }

        return r;
    }
};

class SentenceCorrection : public Handler
{
private:
    Handler* next;

public:
    SentenceCorrection(Handler* next)
    {
        this->next = next;
    }

    Request* handle(Request* r)
    {
        if ((r->getExtent() & 2) == 2)
        {
            string corrected = r->getText();
            corrected += ".";
            r->setText(corrected);
        }

        if (next != nullptr)
        {
            r = next->handle(r);
        }

        return r;
    }
};

int main()
{ 
    Handler* b = new SentenceCorrection(nullptr);
    Handler* a = new CharCorrection(b);

    Request* r = new Request("dzien dobry.", 1);
    a->handle(r);
    cout << r->getText() << "\n";

    Request* r2 = new Request("Dzien dobry", 2);
    a->handle(r2);
    cout << r2->getText() << "\n";

    Request* r3 = new Request("dzien dobry", 3);
    a->handle(r3);
    cout << r3->getText() << "\n";
}