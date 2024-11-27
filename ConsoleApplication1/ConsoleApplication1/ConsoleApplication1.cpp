#include <iostream>
#include <cmath>
#include "Fraction.h"
using std::cin;
using std::cout;
using std::endl;
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

    cout << "equal: ";
    (a.equ(b));

    cout << "\nnot equal: ";
    (a.nte(b));

    cout << "\nGreater-than sign: ";
    (a.gts(b));

    cout << "\nless-than sign: ";
    (a.lts(b));

    return 0;
}