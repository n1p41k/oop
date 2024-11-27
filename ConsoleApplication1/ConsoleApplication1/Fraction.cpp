#include <iostream>
#include <cmath>
#include "Fraction.h"
using namespace std;

Fraction::Fraction()
    : numerator(0)
    , denominator(1)
{}

Fraction::Fraction(int numerator, int denominator)
    : numerator(numerator)
    , denominator(denominator)
{}

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
    Fraction result;
    result.numerator = numerator * b.denominator;
    result.denominator = denominator * b.numerator;
    result.reduce(); // Сокращение результата
    return result;
}

Fraction Fraction::equ(Fraction b)
{
    Fraction result;
    if (numerator * b.denominator == denominator * b.numerator)
    {
        cout << "yes";
    }
    else
    {
        cout << "no";
    }
    return result;
}

Fraction Fraction::nte(Fraction b)
{
    Fraction result;
    if (numerator * b.denominator != denominator * b.numerator)
    {
        cout << "yes";
    }
    else
    {
        cout << "no";
    }
    return result;
}

Fraction Fraction::gts(Fraction b)
{
    Fraction result;
    if (numerator * b.denominator > denominator * b.numerator)
    {
        cout << "yes";
    }
    else
    {
        cout << "no";
    }
    return result;
}

Fraction Fraction::lts(Fraction b)
{
    Fraction result;
    if (numerator * b.denominator < denominator * b.numerator)
    {
        cout << "yes";
    }
    else
    {
        cout << "no";
    }
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