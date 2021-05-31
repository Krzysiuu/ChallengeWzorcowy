#include <iostream>
#include <string>

using namespace std;

bool contains(string a, string b)
{
    if (a.find(b) != string::npos)
        return true;

    return false;
}

class Expression
{
public:
    virtual bool interpret(string) = 0;
};

class TerminalExpression : public Expression
{
private:
    string data;

public:
    TerminalExpression(string data)
    {
        this->data = data;
    }

    bool interpret(string context)
    {
        return contains(context, data);
    }
};

class OrExpression : public Expression
{
private:
    Expression* expression1;
    Expression* expression2;

public:
    OrExpression(Expression* expr1, Expression* expr2)
    {
        expression1 = expr1;
        expression2 = expr2;
    }

    bool interpret(string context)
    {
        return expression1->interpret(context) || expression2->interpret(context);
    }
};

class AndExpression : public Expression
{
private:
    Expression* expression1;
    Expression* expression2;

public:
    AndExpression(Expression* expr1, Expression* expr2)
    {
        expression1 = expr1;
        expression2 = expr2;
    }

    bool interpret(string context)
    {
        return expression1->interpret(context) && expression2->interpret(context);
    }
};

void boolToString(bool x)
{
    if (x)
        cout << "True\n";
    else
        cout << "False\n";
}

int main()
{
    Expression* a = new TerminalExpression("Jacek");
    Expression* b = new TerminalExpression("Ola");
    Expression* marriage = new AndExpression(a, b);

    boolToString(marriage->interpret("Czy ten Jacek i Ola sa w sobie zakochani"));
    boolToString(marriage->interpret("Czy ten Jacek i Magda sa w sobie zakochani"));

    Expression* c = new TerminalExpression("Piwo");
    Expression* d = new TerminalExpression("Wino");
    Expression* kulturalnaposiadowka = new OrExpression(c, d);

    boolToString(kulturalnaposiadowka->interpret("Idziemy na Wino"));
    boolToString(kulturalnaposiadowka->interpret("Idziemy na Piwo"));
    boolToString(kulturalnaposiadowka->interpret("Idziemy na Wodke"));
}