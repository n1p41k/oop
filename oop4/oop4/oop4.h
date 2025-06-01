#pragma once


#include <iostream>
#include <cassert>
#include <vector>
#include "oop3.h"
#include "oop3.cpp"



class BoolMatrix
{
public:
	BoolMatrix();
	BoolMatrix(int rows, int cols, bool value = false);
    BoolMatrix(const char** bits, int rows, int cols);
	BoolMatrix(const BoolMatrix& other);
	~BoolMatrix();
    int rowCount() const;
    int colCount() const;

    void swap(BoolMatrix& other);

    int weight() const;

    BoolVector conjunction() const;
    BoolVector disjunction() const;
    int rowWeight(int j) const;
    void invertBit(int row, int col);
    void setBit(int row, int col, bool value);
    void setBits(int row, int start, int count, bool value);

    // Перегрузки
    BoolMatrix& operator=(const BoolMatrix& other);
    BoolVector& operator[](int row);
    const BoolVector& operator[](int row) const;

    BoolMatrix operator&(const BoolMatrix& other) const;
    BoolMatrix& operator&=(const BoolMatrix& other);

    BoolMatrix operator|(const BoolMatrix& other) const;
    BoolMatrix& operator|=(const BoolMatrix& other);

    BoolMatrix operator^(const BoolMatrix& other) const;
    BoolMatrix& operator^=(const BoolMatrix& other);

    BoolMatrix operator~() const;

    friend std::ostream& operator<<(std::ostream& os, const BoolMatrix& m);
    friend std::istream& operator>>(std::istream& is, BoolMatrix& m);

private:
    int m_rows;
    int m_cols;
    BoolVector* m_matrix;
};
