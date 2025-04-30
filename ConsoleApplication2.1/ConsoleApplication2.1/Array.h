#pragma once
#include <assert.h>
#include <iostream>
#include <algorithm>


template <typename ItemType>
class Array
{
public:
    typedef ItemType* iterator;
    typedef const ItemType* const_iterator;
    typedef ItemType value_type;
    typedef ItemType& reference;
    typedef const ItemType& const_reference;
    typedef ItemType* pointer;
    typedef int difference_type;
    typedef size_t size_type;

public:
    Array(int size = 10);
    Array(const ItemType* arr, int size);  // Constructor from regular array
    Array(const Array& other);
    Array(Array&& other) noexcept;
    ~Array();

    size_t size() const;
    bool empty() const;
    bool isEmpty() const
    {
        return empty();
    }

    iterator begin();
    iterator end();
    const_iterator begin() const;
    const_iterator end() const;

    // Search operations
    iterator find(const ItemType& value);
    const_iterator find(const ItemType& value) const;

    // Insert operations
    bool insert(int index, const ItemType& value);
    void push_front(const ItemType& value);
    void push_back(const ItemType& value);
    bool insert_after(const ItemType& key, const ItemType& value);
    iterator insert(iterator pos, const ItemType& value);

    // Remove operations
    void pop_front();
    void pop_back();
    bool remove(const ItemType& value);
    bool remove_at(int index);
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);

    // Other operations
    void swap(Array& other) noexcept;
    void clear();
    void sort();
    ItemType& max();
    const ItemType& max() const;
    ItemType& min();
    const ItemType& min() const;

    // Operator overloads
    Array& operator=(const Array& other);
    Array& operator=(Array&& other) noexcept;
    ItemType& operator[](int index);
    const ItemType& operator[](int index) const;
    Array operator+(const Array& other) const;
    Array& operator+=(const Array& other);
    bool operator==(const Array& other) const;
    bool operator!=(const Array& other) const;

    // Input/output
    friend std::ostream& operator<<(std::ostream& os, const Array& arr) {
        os << "[";
        for (int i = 0; i < arr.m_size; ++i) {
            os << arr.m_array[i];
            if (i != arr.m_size - 1) os << ", ";
        }
        os << "]";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Array& arr) {
        for (int i = 0; i < arr.m_size; ++i) {
            is >> arr.m_array[i];
        }
        return is;
    }

private:
    ItemType* m_array = nullptr;
    int m_size = 0;
};

template <typename ItemType>
Array<ItemType>::Array(int size)
{
    if (size < 0) size = -size;
    m_size = size;
    m_array = new ItemType[m_size];
    for (int i = 0; i < m_size; i++) {
        m_array[i] = ItemType();
    }
}

template <typename ItemType>
Array<ItemType>::Array(const ItemType* arr, int size) : m_size(size)
{
    m_array = new ItemType[m_size];
    for (int i = 0; i < m_size; i++) {
        m_array[i] = arr[i];
    }
}

template <typename ItemType>
Array<ItemType>::Array(const Array& other)
{
    m_size = other.m_size;
    m_array = new ItemType[m_size];
    for (int i = 0; i < m_size; i++) {
        m_array[i] = other.m_array[i];
    }
}

template <typename ItemType>
Array<ItemType>::Array(Array&& other) noexcept
    : m_array(other.m_array), m_size(other.m_size)
{
    other.m_array = nullptr;
    other.m_size = 0;
}

template <typename ItemType>
Array<ItemType>::~Array()
{
    delete[] m_array;
}

template <typename ItemType>
size_t Array<ItemType>::size() const {
    return m_size;
}

template <typename ItemType>
bool Array<ItemType>::empty() const {
    return m_size == 0;
}

template <typename ItemType>
typename Array<ItemType>::iterator Array<ItemType>::begin() {
    return m_array;
}

template <typename ItemType>
typename Array<ItemType>::iterator Array<ItemType>::end() {
    return m_array + m_size;
}

template <typename ItemType>
typename Array<ItemType>::const_iterator Array<ItemType>::begin() const {
    return m_array;
}

template <typename ItemType>
typename Array<ItemType>::const_iterator Array<ItemType>::end() const {
    return m_array + m_size;
}

template <typename ItemType>
typename Array<ItemType>::iterator Array<ItemType>::find(const ItemType& value) //найти элемент в массиве
{
    for (iterator it = begin(); it != end(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return end();
}

template <typename ItemType>
typename Array<ItemType>::const_iterator Array<ItemType>::find(const ItemType& value) const //найти элемент в массиве
{
    for (const_iterator it = begin(); it != end(); ++it) {
        if (*it == value) {
            return it;
        }
    }
    return end();
}

template <typename ItemType>
bool Array<ItemType>::insert(int index, const ItemType& value) //вставиить элемент в массив
{
    if (index < 0 || index > m_size) return false;

    ItemType* newArray = new ItemType[m_size + 1];
    for (int i = 0; i < index; i++) {
        newArray[i] = m_array[i];
    }

    newArray[index] = value;

    for (int i = index; i < m_size; i++) {
        newArray[i + 1] = m_array[i];
    }

    delete[] m_array;
    m_array = newArray;
    m_size++;

    return true;
}

template <typename ItemType>
void Array<ItemType>::push_front(const ItemType& value)
{
    insert(0, value);
}

template <typename ItemType>
void Array<ItemType>::push_back(const ItemType& value)
{
    insert(m_size, value);
}

template <typename ItemType>
bool Array<ItemType>::insert_after(const ItemType& key, const ItemType& value)
{
    iterator it = find(key);
    if (it == end()) return false;

    int index = it - begin();
    return insert(index + 1, value);
}

template <typename ItemType>
typename Array<ItemType>::iterator Array<ItemType>::insert(iterator pos, const ItemType& value)
{
    int index = pos - begin();
    if (insert(index, value)) {
        return begin() + index;
    }
    return end();
}

template <typename ItemType>
void Array<ItemType>::pop_front()
{
    if (m_size == 0) return;
    remove_at(0);
}

template <typename ItemType>
void Array<ItemType>::pop_back()
{
    if (m_size == 0) return;
    remove_at(m_size - 1);
}

template <typename ItemType>
bool Array<ItemType>::remove(const ItemType& value)
{
    iterator it = find(value);
    if (it == end()) return false;

    return remove_at(it - begin());
}

template <typename ItemType>
bool Array<ItemType>::remove_at(int index)
{
    if (index < 0 || index >= m_size) return false;

    ItemType* newArray = new ItemType[m_size - 1];
    for (int i = 0; i < index; i++) {
        newArray[i] = m_array[i];
    }

    for (int i = index + 1; i < m_size; i++) {
        newArray[i - 1] = m_array[i];
    }

    delete[] m_array;
    m_array = newArray;
    m_size--;

    return true;
}

template <typename ItemType>
typename Array<ItemType>::iterator Array<ItemType>::erase(iterator pos) //удаление позиции
{
    int index = pos - begin();
    if (remove_at(index)) {
        return begin() + index;
    }
    return end();
}

template <typename ItemType>
typename Array<ItemType>::iterator Array<ItemType>::erase(iterator first, iterator last) //удаление диапозона
{
    int start = first - begin();
    int end = last - begin();
    int count = end - start;

    if (start < 0 || end > m_size || count <= 0) return end();

    ItemType* newArray = new ItemType[m_size - count];
    for (int i = 0; i < start; i++) {
        newArray[i] = m_array[i];
    }

    for (int i = end; i < m_size; i++) {
        newArray[i - count] = m_array[i];
    }

    delete[] m_array;
    m_array = newArray;
    m_size -= count;

    return begin() + start;
}

template <typename ItemType>
void Array<ItemType>::swap(Array& other) noexcept
{
    std::swap(m_array, other.m_array);
    std::swap(m_size, other.m_size);
}

template <typename ItemType>
void Array<ItemType>::clear()
{
    delete[] m_array;
    m_array = nullptr;
    m_size = 0;
}

template <typename ItemType>
void Array<ItemType>::sort()
{
    std::sort(begin(), end());
}

template <typename ItemType>
ItemType& Array<ItemType>::max()
{
    assert(m_size > 0);
    return *std::max_element(begin(), end());
}

template <typename ItemType>
const ItemType& Array<ItemType>::max() const
{
    assert(m_size > 0);
    return *std::max_element(begin(), end());
}

template <typename ItemType>
ItemType& Array<ItemType>::min()
{
    assert(m_size > 0);
    return *std::min_element(begin(), end());
}

template <typename ItemType>
const ItemType& Array<ItemType>::min() const
{
    assert(m_size > 0);
    return *std::min_element(begin(), end());
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(const Array& other)
{
    if (this != &other) {
        Array tmp(other);
        swap(tmp);
    }
    return *this;
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator=(Array&& other) noexcept
{
    if (this != &other) {
        delete[] m_array;
        m_array = other.m_array;
        m_size = other.m_size;
        other.m_array = nullptr;
        other.m_size = 0;
    }
    return *this;
}

template <typename ItemType>
ItemType& Array<ItemType>::operator[](int index) {
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

template <typename ItemType>
const ItemType& Array<ItemType>::operator[](int index) const {
    assert(index >= 0 && index < m_size);
    return m_array[index];
}

template <typename ItemType>
Array<ItemType> Array<ItemType>::operator+(const Array& other) const
{
    Array result(m_size + other.m_size);
    for (int i = 0; i < m_size; ++i) {
        result[i] = m_array[i];
    }
    for (int i = 0; i < other.m_size; ++i) {
        result[m_size + i] = other[i];
    }
    return result;
}

template <typename ItemType>
Array<ItemType>& Array<ItemType>::operator+=(const Array& other) {
    *this = *this + other;
    return *this;
}

template <typename ItemType>
bool Array<ItemType>::operator==(const Array& other) const
{
    if (m_size != other.m_size) return false;
    for (int i = 0; i < m_size; ++i) {
        if (m_array[i] != other.m_array[i]) {
            return false;
        }
    }
    return true;
}

template <typename ItemType>
bool Array<ItemType>::operator!=(const Array& other) const
{
    return !(*this == other);
}