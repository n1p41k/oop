#pragma once
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cstring>

class BoolVector
{
    class Rank;
    static const int CellSize = 8; 

public:
    using Cell = unsigned char;
    BoolVector(int length = CellSize);
    BoolVector(int length, bool value);
    BoolVector(const char* bits);
    BoolVector(const BoolVector& other);
    ~BoolVector();

    int length() const;
    void swap(BoolVector& other);

    bool bitValue(int index) const;
    void setBitValue(int index, bool value);
    void invert();
    void invertBit(int index);
    void setBits(int index, int count, bool value);
    void setAll(bool value);
    int weight() const;

    BoolVector& operator=(const BoolVector& other);
    Rank operator[](int index);
    bool operator[](int index) const;

    BoolVector operator~() const;
    BoolVector operator&(const BoolVector& other) const;
    BoolVector& operator&=(const BoolVector& other);
    BoolVector operator|(const BoolVector& other) const;
    BoolVector& operator|=(const BoolVector& other);
    BoolVector operator^(const BoolVector& other) const;
    BoolVector& operator^=(const BoolVector& other);

    BoolVector operator<<(int shift) const;
    BoolVector& operator<<=(int shift);
    BoolVector operator>>(int shift) const;
    BoolVector& operator>>=(int shift);

    friend std::ostream& operator<<(std::ostream& os, const BoolVector& bv)
    {
        for (int i = 0; i < bv.m_length; ++i)
            os << (bv.bitValue(i) ? '1' : '0');
        return os;
    }

    friend std::istream& operator>>(std::istream& is, BoolVector& bv)
    {
        std::string input;
        is >> input;
        int len = input.length();
        if (len != bv.m_length)
        {
            delete[] bv.m_cells;
            bv.m_length = len;
            bv.m_cellCount = (len + CellSize - 1) / CellSize;
            bv.m_cells = new Cell[bv.m_cellCount]{};
        }
        for (int i = 0; i < len; ++i)
            bv.setBitValue(i, input[i] == '1');
        return is;
    }

private:
    Cell* m_cells = nullptr;
    int m_cellCount = 0;
    int m_length = 0;
};

class BoolVector::Rank
{
public:
    Rank(Cell& cell, int index) : cell(cell), index(index) {}
    Rank& operator=(bool value)
    {
        Cell mask = 1 << (CellSize - 1 - index);
        if (value)
            cell |= mask;
        else
            cell &= ~mask;
        return *this;
    }
    operator bool() const
    {
        Cell mask = 1 << (CellSize - 1 - index);
        return cell & mask;
    }

private:
    Cell& cell;
    int index;
};
