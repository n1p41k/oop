#pragma once
#include <iostream>
#include <string>
#include <cassert>


template <typename T>
class List {
    struct Node {
        T value;
        Node* next;
        Node* prev;
        Node(const T& val, Node* n = nullptr, Node* p = nullptr)
            : value(val), next(n), prev(p) 
        {}
    };

public:
    class Iterator {
    public:
        Iterator(Node* node) : node(node) {}
        T& operator*() { 
            return node->value; 
        }
        Iterator& operator++() { 
            node = node->next; return *this; 
        }
        bool operator!=(const Iterator& other) const { 
            return node != other.node; 
        }
        Node* getNode() const { 
            return node; 
        }
    private:
        Node* node;
    };

    List();
    List(const List& other);
    List& operator=(const List& other);
    ~List();

    void push_back(const T& value);
    void push_front(const T& value);
    void pop_back();
    void pop_front();
    void clear();
    int size() const;
    bool isEmpty() const;

    Iterator begin();
    Iterator end();

    Iterator find(const T& value);
    void insert(Iterator pos, const T& value);
    void erase(Iterator pos);

    T& operator[](int index);

    void print() const;

private:
    int m_size = 0;
    Node* head;
    Node* tail;
    int count;
};


template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), count(0) 
{}

template <typename T>
List<T>::List(const List& other) : List() {
    for (Node* p = other.head; p; p = p->next)
        push_back(p->value);
}

template <typename T>
List<T>& List<T>::operator=(const List& other) {
    if (this != &other) {
        clear();
        for (Node* p = other.head; p; p = p->next)
            push_back(p->value);
    }
    return *this;
}

template <typename T>
List<T>::~List() {
    clear();
}

template <typename T>
void List<T>::push_back(const T& value) {
    Node* node = new Node(value, nullptr, tail);
    if (tail) tail->next = node;
    tail = node;
    if (!head) head = node;
    ++count;
    assert(tail->next == nullptr);
}

template <typename T>
void List<T>::push_front(const T& value) {
    Node* node = new Node(value, head, nullptr);
    if (head) head->prev = node;
    head = node;
    if (!tail) tail = node;
    ++count;
    assert(head->prev == nullptr);
}

template <typename T>
void List<T>::pop_back() {
    if (!tail) return;
    Node* tmp = tail;
    tail = tail->prev;
    if (tail) tail->next = nullptr;
    else head = nullptr;
    delete tmp;
    --count;
}


template <typename T>
void List<T>::pop_front() {
    if (!head) return;
    Node* tmp = head;
    head = head->next;
    if (head) head->prev = nullptr;
    else tail = nullptr;
    delete tmp;
    --count;
}

template <typename T>
void List<T>::clear() {
    Node* current = head;
    while (current) {
        Node* tmp = current;
        current = current->next;
        delete tmp;
    }
    head = tail = nullptr;
    count = 0;
}

template <typename T>
int List<T>::size() const {
    return count;
}

template <typename T>
bool List<T>::isEmpty() const {
    return count == 0;
}

template <typename T>
typename List<T>::Iterator List<T>::begin() {
    return Iterator(head);
}

template <typename T>
typename List<T>::Iterator List<T>::end() {
    return Iterator(nullptr);
}

template <typename T>
typename List<T>::Iterator List<T>::find(const T& value) {
    Node* p = head;
    while (p) {
        if (p->value == value)
            return Iterator(p);
        p = p->next;
    }
    return end();
}

template <typename T>
void List<T>::insert(Iterator pos, const T& value) {
    Node* node = pos.getNode();
    if (!node) {
        push_back(value);
        return;
    }
    Node* newNode = new Node(value, node, node->prev);
    if (node->prev) node->prev->next = newNode;
    else head = newNode;
    node->prev = newNode;
    ++count;
}

template <typename T>
void List<T>::erase(Iterator pos) {
    Node* node = pos.getNode();
    if (!node) return;
    if (node->prev) node->prev->next = node->next;
    else head = node->next;
    if (node->next) node->next->prev = node->prev;
    else tail = node->prev;
    delete node;
    --count;
}

template <typename T>
T& List<T>::operator[](int index) {
    Node* p = head;
    for (int i = 0; i < index; ++i) {
        if (p) p = p->next;
    }
    if (p != NULL) {
        return p->value;
    }
}

template <typename T>
void List<T>::print() const {
    Node* p = head;
    while (p) {
        std::cout << p->value << ' ';
        p = p->next;
    }
    std::cout << '\n';
}
