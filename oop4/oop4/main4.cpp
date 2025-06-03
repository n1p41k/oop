#include <iostream>
#include "oop4.h"

int main()
{
	BoolMatrix m1(3, 3);
	std::cout << m1 << std::endl;
	BoolMatrix m2(3, 3, true);
	std::cout << m2 << std::endl;
	BoolMatrix m22(3, 3, false);
	std::cout << m22 << std::endl;
	BoolMatrix m3(m2);
	std::cout << m3 << std::endl;
	BoolMatrix m4;
	m4 = m2;
	std::cout << m4 << std::endl;
	m4.swap(m1);
	std::cout << m4 << std::endl;
	const char* bits[] = { "101", "010", "111" };
	BoolMatrix m5(bits, 3, 3);
	std::cout << m5 << std::endl;
	BoolMatrix m6(2, 2, false);
	m6.setBit(0, 0, true);
	m6.setBit(1, 1, true);
	std::cout << m6 << std::endl;
	m6.invertBit(0, 0);
	std::cout << m6 << std::endl;
	m6.setBits(0, 0, 2, true);
	std::cout << m6 << std::endl;
	const char* bits1[] = { "101", "010" };
	const char* bits2[] = { "110", "011" };
	BoolMatrix m7(bits1, 2, 3);
	BoolMatrix m8(bits2, 2, 3);
	std::cout <<( m7 & m8 )<< std::endl;
	std::cout << (m7 | m8) << std::endl;
	std::cout << (m7 ^ m8) << std::endl;
	std::cout << (~m7) << std::endl;
	return 0;
}