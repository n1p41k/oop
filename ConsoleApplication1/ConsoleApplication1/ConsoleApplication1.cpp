#include <iostream>
#include <cmath>
using namespace std;

//Наш код
class Fraction
{
public:
    Fraction();
    Fraction(int numerator, int denominator);
    ~Fraction() = default;
    void print();

    Fraction sum(Fraction b);   //Example: c = a.sum(b)
    Fraction sub(Fraction b);
    Fraction mul(Fraction b);
    Fraction div(Fraction b);

    void reduce(); //Сокращение дроби

    int getNumerator();
    int getDenominator();

    void setNumerator(int value);
    void setDenominator(int value);

    // Новые методы:
    Fraction fromDouble(double value, int precision = 3);
    Fraction toMixedNumber();

public:
    int numerator;
    int denominator;
};

Fraction::Fraction() : numerator(0), denominator(1) {}

Fraction::Fraction(int numerator, int denominator) : numerator(numerator), denominator(denominator)
{
    if (denominator == 0) {
        cerr << "Fraction::Fraction: error: denominator is 0, setting to 1.";
        denominator = 1;
    }
}

void Fraction::print()
{
    cout << numerator << "/" << denominator << endl;
}

Fraction Fraction::sum(Fraction b)
{
    Fraction result;
    result.numerator = numerator * b.denominator + denominator * b.numerator;
    result.denominator = denominator * b.denominator;
    result.reduce(); // Сокращение результата
    return result;
}

Fraction Fraction::sub(Fraction b)
{
    Fraction result;
    result.numerator = numerator * b.denominator - denominator * b.numerator;
    result.denominator = denominator * b.denominator;
    result.reduce(); // Сокращение результата
    return result;
}

Fraction Fraction::mul(Fraction b)
{
    Fraction result;
    result.numerator = numerator * b.numerator;
    result.denominator = denominator * b.denominator;
    result.reduce(); // Сокращение результата
    return result;
}

Fraction Fraction::div(Fraction b)
{
    //Особый случай:
    if (b.numerator == 0) {
        cerr << "Fraction::div: error: b.numerator is 0, result will be 0/1.";
        return Fraction(0, 1); //Fraction(1, 1); или любую на ваше усмотрение
        cerr << "Fraction::div: error: b.numerator is 0, won't divide.";
        return *this;
    }

    Fraction result;
    result.numerator = numerator * b.denominator;
    result.denominator = denominator * b.numerator;
    result.reduce(); // Сокращение результата
    return result;
}

void Fraction::reduce()
{
    if (denominator == 0) {
        cerr << "Fraction::reduce: error: denominator is 0, won't reduce.";
        return;
    }

    int gcd = 1;
    for (int i = 1; i <= min(abs(numerator), abs(denominator)); i++) {
        if (numerator % i == 0 && denominator % i == 0) {
            gcd = i;
        }
    }

    numerator /= gcd;
    denominator /= gcd;
}

int Fraction::getNumerator()
{
    return numerator;
}

int Fraction::getDenominator()
{
    return denominator;
}

void Fraction::setNumerator(int value)
{
    numerator = value;
}

void Fraction::setDenominator(int value)
{
    if (value == 0) {
        cerr << "Fraction::setDenominator: error: value is 0, won't assign.";
        return;
    }

    denominator = value;
}

// Новые методы:
Fraction Fraction::fromDouble(double value, int precision)
{
    int integerPart = static_cast<int>(value);
    double decimalPart = value - integerPart;

    int denominator = pow(10, precision);
    int numerator = static_cast<int>(round(decimalPart * denominator));

    return Fraction(integerPart * denominator + numerator, denominator);
}

Fraction Fraction::toMixedNumber()
{
    int wholePart = numerator / denominator;
    int remainder = numerator % denominator;

    return Fraction(remainder, denominator);
}
//Код другого разработчика (который использует наш класс)
//Fraction a(1, 2), b(3, 4), c(4, 3), d(1, 1), e(3, 1), f(4, 9), g(5, 5);
Fraction foo1(Fraction& a, Fraction& b, Fraction c)
{
    c.numerator = 0;
    c.denominator = 1;
    c.sum(a);
    // Проверка на деление на 0 в b.div(c)
    if (c.numerator == 0) {
        cerr << "foo1: error: division by zero, returning 0/1" << endl;
        return Fraction(0, 1); // Возвращаем 0/1
    }
    return b.div(c).sum(c); //h = 3/4 : 0/1 + 0/1 = 3/0 + 0/1 = 3/0
}

void foo2(Fraction& h, Fraction& d, Fraction& e, Fraction& a)
{
    e.numerator -= d.numerator;
    // e.denominator -= d.denominator;  //Как обработать???????
    // Проверка на деление на 0 в e.setDenominator
    if (e.getDenominator() - d.getDenominator() == 0) {
        cerr << "foo2: error: division by zero, skipping operation" << endl;
        return;
    }
    e.setDenominator(e.getDenominator() - d.getDenominator()); //Выведет ошибку в консоль!
    //e = 2/0
    a = d.mul(h).sub(e);
    //a = 1/1 * 3/0 - 2/0 = 3/0 - 2/0 = 1/0, если 
    // в вычитании обработан случай равенства знаменателей; иначе 0/0
}

void foo3(Fraction& g, Fraction& h, Fraction& a)
{
    // Проверка на деление на 0 в g.div(h)
    if (h.numerator == 0) {
        cerr << "foo3: error: division by zero, skipping operation" << endl;
        return;
    }
    g = g.div(h).mul(a);
    //g = 5/5 : 3/0 * 1/0 = 0/0
}
void foo()
{
    Fraction a(1, 2), b(3, 4), c(4, 3), d(1, 1), e(3, 1), f(4, 9), g(5, 5);

    Fraction h = foo1(a, b, c);
    foo2(h, d, e, a);
    foo3(g, h, a);
    //a = 1/0 (или 0/0)
    //g = 0/0
    //h = 3/0
    a.reduce();
    g.reduce();
    h.reduce();

}
int main()
{
    // Преобразование десятичной дроби в обыкновенную:
    double decimal = 2.5;
    Fraction f1 = Fraction().fromDouble(decimal, 2);
    cout << "transformation " << decimal << " in normal fraction: ";
    f1.print();

    // Преобразование в смешанное число:
    Fraction f2(11, 4);
    cout << "transformation " << 11 << "/4 in mixed fraction: ";
    f2.toMixedNumber().print();

    // Остальной код:
    Fraction a(1, 2), b(3, 4);

    cout << "using fraction: " << endl;
    cout << "a: "; a.print();
    cout << "b: "; b.print();

    cout << "summ: ";
    (a.sum(b)).print();

    cout << "difference: ";
    (a.sub(b)).print();

    cout << "production: ";
    (a.mul(b)).print();

    cout << "quotient: ";
    (a.div(b)).print();

    return 0;
}