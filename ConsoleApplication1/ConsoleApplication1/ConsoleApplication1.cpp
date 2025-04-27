#include <iostream>
#include <cmath>
#include "Fraction.h"
using std::cin;
using std::cout;
using std::endl;
int main()
{
    Fraction a(1, 2), b(3, 4), c(11,4);

    cout << "using fraction: " << endl;
    cout << "a: "; a.print();
    cout << "b: "; b.print();
    cout << "c: "; c.print();

    cout << "summ(a nad b): ";
    (a.sum(b)).print();

    cout << "difference(a nad b): ";
    (a.sub(b)).print();

    cout << "production(a nad b): ";
    (a.mul(b)).print();

    cout << "quotient(a nad b): ";
    (a.div(b)).print();

    cout << "equal(a nad b): ";
    (a.equ(b));

    cout << "\nnot equal(a nad b): ";
    (a.nte(b));

    cout << "\nGreater-than sign(a nad b): ";
    (a.gts(b));

    cout << "\nless-than sign(a nad b): ";
    (a.lts(b));

    cout << "\ndegree first: ";
    (a.deg(a)).print();

    cout << "degree second: ";
    (b.deg(b)).print();

    cout << "degree third: ";
    (c.deg(c)).print();

    cout << "Mixed number(c): ";
    (c.toMixedNumber(c)).print();

    cout << "fromDouble(a): ";
    (a.fromDouble(a)).print();

    cout << "fromDouble(b): ";
    (b.fromDouble(b)).print();

    cout << "fromDouble(c): ";
    (c.fromDouble(c)).print();

    return 0;
}