#include "oop4.h"

BoolMatrix::BoolMatrix()
    :m_rows(0), m_cols(0), m_matrix(nullptr)
{}

BoolMatrix::BoolMatrix(int rows, int cols, bool value)
    : m_rows(rows), m_cols(cols), m_matrix(rows ? new BoolVector[rows] : nullptr)
{
    for (int i = 0; i < rows; ++i)
        m_matrix[i] = BoolVector(cols, value);
}

BoolMatrix::BoolMatrix(const char** bits, int rows, int cols)
    : BoolMatrix(rows, cols)  
{
    for (int i = 0; i < rows; ++i)
        m_matrix[i] = BoolVector(bits[i]);
}

BoolMatrix::BoolMatrix(const BoolMatrix& other)
    : BoolMatrix(other.m_rows, other.m_cols)  
{
    for (int i = 0; i < m_rows; ++i)
        m_matrix[i] = other.m_matrix[i];
}

BoolMatrix::~BoolMatrix() {
    delete[] m_matrix;
}

int BoolMatrix::rowCount() const 
{ 
    return m_rows; 
}
int BoolMatrix::colCount() const 
{
    return m_cols; 
}

void BoolMatrix::swap(BoolMatrix& other) {
    std::swap(m_rows, other.m_rows);
    std::swap(m_cols, other.m_cols);
    std::swap(m_matrix, other.m_matrix);
}

int BoolMatrix::weight() const {
    int total = 0;
    for (int i = 0; i < m_rows; ++i)
        total += m_matrix[i].weight();
    return total;
}

int BoolMatrix::rowWeight(int row) const 
{
    return m_matrix[row].weight();
}

BoolVector BoolMatrix::conjunction() const
{
    BoolVector result = m_matrix[0];
    for (int i = 1; i < m_rows; ++i)
        result &= m_matrix[i];
    return result;
}

BoolVector BoolMatrix::disjunction() const
{
    BoolVector result = m_matrix[0];
    for (int i = 1; i < m_rows; ++i)
        result |= m_matrix[i];
    return result;
}

void BoolMatrix::invertBit(int row, int col)
{
    m_matrix[row].invertBit(col);
}

void BoolMatrix::setBit(int row, int col, bool value)
{
    m_matrix[row].setBitValue(col, value);
}

void BoolMatrix::setBits(int row, int start, int count, bool value) 
{
    m_matrix[row].setBits(start, count, value);
}

BoolMatrix& BoolMatrix::operator=(const BoolMatrix& other) 
{
    if (this != &other) {
        BoolMatrix temp(other);
        swap(temp);
    }
    return *this;
}

BoolVector& BoolMatrix::operator[](int index) {
    return m_matrix[index];
}

const BoolVector& BoolMatrix::operator[](int index) const {
    return m_matrix[index];
}

BoolMatrix& BoolMatrix::operator&=(const BoolMatrix& other) {
    for (int i = 0; i < m_rows; ++i)
        m_matrix[i] &= other.m_matrix[i];
    return *this;
}

BoolMatrix BoolMatrix::operator&(const BoolMatrix& other) const {
    BoolMatrix result(*this);
    return result &= other;
}

BoolMatrix& BoolMatrix::operator|=(const BoolMatrix& other) {
    for (int i = 0; i < m_rows; ++i)
        m_matrix[i] |= other.m_matrix[i];
    return *this;
}

BoolMatrix BoolMatrix::operator|(const BoolMatrix& other) const {
    BoolMatrix result(*this);
    return result |= other;
}

BoolMatrix& BoolMatrix::operator^=(const BoolMatrix& other) {
    for (int i = 0; i < m_rows; ++i)
        m_matrix[i] ^= other.m_matrix[i];
    return *this;
}

BoolMatrix BoolMatrix::operator^(const BoolMatrix& other) const {
    BoolMatrix result(*this);
    return result ^= other;
}

BoolMatrix BoolMatrix::operator~() const {
    BoolMatrix result(*this);
    for (int i = 0; i < m_rows; ++i)
        result[i].invert();
    return result;
}

std::ostream& operator<<(std::ostream& os, const BoolMatrix& matrix) {
    for (int i = 0; i < matrix.m_rows; ++i) {
        for (int j = 0; j < matrix.m_cols; ++j)
            os << matrix.m_matrix[i][j];
        os << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, BoolMatrix& m) 
{
    int rows, cols;
    is >> rows >> cols;

    delete[] m.m_matrix;
    m.m_rows = rows;
    m.m_cols = cols;
    m.m_matrix = new BoolVector[rows];

    for (int i = 0; i < rows; ++i)
        is >> m.m_matrix[i];

    return is;
}