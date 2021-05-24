#include <iostream>
#include <string>

using namespace std;

class Translator
{
public:
    virtual string translate() = 0;
};

class FileReader
{
private:
    string file;

public:
    FileReader(string file_text)
    {
        file = file_text;
    }

    string sendText()
    {
        return file;
    }
};

class Adapter : public Translator
{
private:
    FileReader* reader;

public:
    Adapter(FileReader* reader)
    {
        this->reader = reader;
    }

    string translate()
    {
        string to_translate = reader->sendText();
        return to_translate + " \\przetlumaczony na inny jezyk \n";
    }
};



int main()
{
    FileReader* reader = new FileReader("Hakuna matata");
    Translator* translator = new Adapter(reader);

    cout << translator->translate();
}
