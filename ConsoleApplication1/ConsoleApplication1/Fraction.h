#pragma once
class Fraction
{
public:
    Fraction();
    int numerator;
    int denominator;
    Fraction(int numerator, int denominator);
    ~Fraction() = default;
    void print();

    Fraction sum(Fraction b);   //Example: c = a.sum(b)
    Fraction sub(Fraction b);
    Fraction mul(Fraction b);
    Fraction div(Fraction b);
    Fraction equ(Fraction b);
    Fraction nte(Fraction b);
    Fraction gts(Fraction b);  //Greater - than sign
    Fraction lts(Fraction b);  //less - than sign
    float nfr();  //common fraction

    void reduce(); //Сокращение дроби

    int getNumerator();
    int getDenominator();

    void setNumerator(int value);
    void setDenominator(int value);

    // Новые методы:
    Fraction fromDouble(double value, int precision = 3);
    Fraction toMixedNumber();
};