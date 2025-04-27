#pragma once
class Fraction
{
public:
    Fraction();
    Fraction(int numerator, int denominator);
    ~Fraction() = default;
    void print();
    void reduce(); //Сокращение дроби
    int getNumerator();
    int getDenominator();
    void setNumerator(int value);
    void setDenominator(int value);
    Fraction sum(Fraction b);   
    Fraction sub(Fraction b);
    Fraction mul(Fraction b);
    Fraction div(Fraction b);
    Fraction equ(Fraction b);
    Fraction nte(Fraction b);
    Fraction gts(Fraction b);  //Greater - than sign
    Fraction lts(Fraction b);
    Fraction deg(Fraction b); //degree
    Fraction fromDouble(Fraction b);
    Fraction toMixedNumber(Fraction b);
private:
    int numerator;
    int denominator;
};