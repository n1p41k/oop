#include "oop3.h"

BoolVector::BoolVector(int length)
    : m_length(length)
{
    assert(length >= 0);
    m_cellCount = (length + CellSize - 1) / CellSize;
    m_cells = new Cell[m_cellCount]{};
}

BoolVector::BoolVector(int length, bool value)
    : m_length(length)
{
    assert(length >= 0);
    m_cellCount = (length + CellSize - 1) / CellSize;
    m_cells = new Cell[m_cellCount];

    for (int i = 0; i < m_length; ++i) {
        setBitValue(i, value);
    }
}

BoolVector::BoolVector(const char* bits)
{
    m_length = std::strlen(bits);
    m_cellCount = (m_length + CellSize - 1) / CellSize;
    m_cells = new Cell[m_cellCount]{};
    for (int i = 0; i < m_length; ++i)
        setBitValue(i, bits[i] == '1');
}

BoolVector::BoolVector(const BoolVector& other)
    : m_length(other.m_length), m_cellCount(other.m_cellCount)
{
    m_cells = new Cell[m_cellCount];
    std::copy(other.m_cells, other.m_cells + m_cellCount, m_cells);
}

BoolVector::~BoolVector()
{
    delete[] m_cells;
}

int BoolVector::length() const
{ 
    return m_length; 
}

void BoolVector::swap(BoolVector& other)
{
    std::swap(m_cells, other.m_cells);
    std::swap(m_cellCount, other.m_cellCount);
    std::swap(m_length, other.m_length);
}

bool BoolVector::bitValue(int index) const
{
    assert(index >= 0 && index < m_length);
    Cell mask = 1 << (CellSize - 1 - (index % CellSize));
    return m_cells[index / CellSize] & mask;
}

void BoolVector::setBitValue(int index, bool value)
{
    assert(index >= 0 && index < m_length);
    Cell mask = 1 << (CellSize - 1 - (index % CellSize));
    if (value)
        m_cells[index / CellSize] |= mask;
    else
        m_cells[index / CellSize] &= ~mask;
}

void BoolVector::invert()
{
    for (int i = 0; i < m_length; ++i)
    {
        invertBit(i);
    }
}

void BoolVector::invertBit(int index)
{
    assert(index >= 0 && index < m_length);
    Cell mask = 1 << (CellSize - 1 - (index % CellSize));
    m_cells[index / CellSize] ^= mask;
}

void BoolVector::setBits(int index, int count, bool value)
{
    assert(index >= 0 && index + count <= m_length);
    for (int i = 0; i < count; ++i)
        setBitValue(index + i, value);
}

void BoolVector::setAll(bool value)
{
    for (int i = 0; i < m_length; ++i)
    {
        setBitValue(i, value);
    }
}

int BoolVector::weight() const
{
    int count = 0;
    for (int i = 0; i < m_length; ++i)
        if (bitValue(i)) ++count;
    return count;
}

BoolVector& BoolVector::operator=(const BoolVector& other)
{
    if (this != &other)
    {
        Cell* new_cells = new Cell[other.m_cellCount];
        std::copy(other.m_cells, other.m_cells + other.m_cellCount, new_cells);
        delete[] m_cells;
        m_cells = new_cells;
        m_cellCount = other.m_cellCount;
        m_length = other.m_length;
    }
    return *this;
}

BoolVector::Rank BoolVector::operator[](int index)
{
    assert(index >= 0 && index < m_length);
    return Rank(m_cells[index / CellSize], index % CellSize);
}

bool BoolVector::operator[](int index) const
{
    return bitValue(index);
}

BoolVector BoolVector::operator~() const
{
    BoolVector result(*this);
    result.invert();
    return result;
}

BoolVector BoolVector::operator&(const BoolVector& other) const
{
    assert(m_length == other.m_length);
    BoolVector result(m_length);
    for (int i = 0; i < m_cellCount; ++i)
        result.m_cells[i] = m_cells[i] & other.m_cells[i];
    return result;
}

BoolVector& BoolVector::operator&=(const BoolVector& other)
{
    assert(m_length == other.m_length);
    for (int i = 0; i < m_cellCount; ++i)
        m_cells[i] &= other.m_cells[i];
    return *this;
}

BoolVector BoolVector::operator|(const BoolVector& other) const
{
    assert(m_length == other.m_length);
    BoolVector result(m_length);
    for (int i = 0; i < m_cellCount; ++i)
        result.m_cells[i] = m_cells[i] | other.m_cells[i];
    return result;
}

BoolVector& BoolVector::operator|=(const BoolVector& other)
{
    assert(m_length == other.m_length);
    for (int i = 0; i < m_cellCount; ++i)
        m_cells[i] |= other.m_cells[i];
    return *this;
}

BoolVector BoolVector::operator^(const BoolVector& other) const
{
    assert(m_length == other.m_length);
    BoolVector result(m_length);
    for (int i = 0; i < m_cellCount; ++i)
        result.m_cells[i] = m_cells[i] ^ other.m_cells[i];
    return result;
}

BoolVector& BoolVector::operator^=(const BoolVector& other)
{
    assert(m_length == other.m_length);
    for (int i = 0; i < m_cellCount; ++i)
        m_cells[i] ^= other.m_cells[i];
    return *this;
}

BoolVector BoolVector::operator<<(int shift) const
{
    BoolVector result(m_length);
    for (int i = 0; i < m_length - shift; ++i)
        result.setBitValue(i, bitValue(i + shift));
    return result;
}

BoolVector& BoolVector::operator<<=(int shift)
{
    *this = *this << shift;
    return *this;
}

BoolVector BoolVector::operator>>(int shift) const
{
    BoolVector result(m_length);
    for (int i = shift; i < m_length; ++i)
        result.setBitValue(i, bitValue(i - shift));
    return result;
}

BoolVector& BoolVector::operator>>=(int shift)
{
    *this = *this >> shift;
    return *this;
}

