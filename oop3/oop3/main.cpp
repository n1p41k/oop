#include "oop3.h"


int main() {
    std::cout << "[Test 1] Default constructor ";
    BoolVector bv1;
    std::cout << bv1 << std::endl;
    std::cout << "[Test 2] Constructor with length and value: ";
    BoolVector bv2(16, true);
    std::cout << bv2 << std::endl;
    std::cout << "[Test 3] Constructor from string: ";
    const char* bits = "10101010";
    BoolVector bv3(bits);
    std::cout << bv3 << std::endl;
    std::cout << "[Test 4] Copy constructor(copy from test 2): ";
    BoolVector bv4 = bv2;
    std::cout << bv4 << std::endl;
    std::cout << "[Test 5] Assignment and swap: ";
    BoolVector a(8, true);
    BoolVector b(8, false);
    std::cout << "common bv "<< a <<",";
    std::cout << "common bv "<< b << ",";
    a = b;
    std::cout << "after assigment " << a << ",";
    BoolVector c(8, true), d(8, false); 
    c.swap(d);
    std::cout << "after swap " << c << std::endl;
    std::cout << "[Test 6] Bit operations: ";
    BoolVector bv5(8);
    std::cout <<"common bv" << bv5 <<",";
    bv5.setBitValue(0, true);
    std::cout << "after set 1 in index 0 " << bv5 << ",";
    bv5.setBitValue(7, true);
    std::cout << "after set 1 in index 7 " << bv5 << ",";
    bv5.invertBit(0);
    std::cout << "after invert index 0 " << bv5 << ",";
    bv5.invert();
    std::cout << "after invert bv " << bv5 << ",";
    bv5.setBits(2, 3, false);
    std::cout << "after set 2 and 3 bit " << bv5 << ",";
    bv5.setAll(false);
    std::cout << "after set all " << bv5 << std::endl;
    std::cout << "[Test 7] Logical operators: ";
    BoolVector a1(8);
    BoolVector b1(8);
    a1.setBitValue(0, true);
    std::cout << "common bv " << a1 << ",";
    b1.setBitValue(1, true);
    std::cout << "common bv " << b1 << ",";
    BoolVector c1 = a1 | b1;
    std::cout << "operation or " << c1 << ",";
    c1 &= a1;
    std::cout << "operation and " << c1 << ",";
    c1 ^= b1;
    std::cout << "operation xor " << c1 << ",";
    c1 = ~c1;
    std::cout << "operation inversy " << c1 <<std::endl;
    std::cout << "[Test 8] Weight function: ";
    BoolVector bv7(10);
    bv7.setBitValue(0, true);
    bv7.setBitValue(8, true);
    std::cout <<"common bv "<< bv7 << ",";
    std::cout <<"weight " << bv7.weight() << std::endl;

    return 0;
}