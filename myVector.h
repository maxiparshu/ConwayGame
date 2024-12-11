#pragma once
#include <iostream>
#include <memory>
template <typename T>
class MyVector {
private:
    T* data;// массив в котором лежат все данные
    int _size;// текущее кол-во элементов
    int capacity;// максимальное кол-во элементов

    void deleteNode(int); //удаляет элемент с номером

    int find(const T&); // находит индекс элемент, если нету элемента то -1

public:


    MyVector(); // конструктор

    ~MyVector(); // десттуктор

    int size();// возвращет кол-во текущее элементов

    bool indexIsCorrect(int); // проверяет правильность индекса

    bool contains(const T&); // true - содержит

    void resize(int); // пересохздает массив с новой длиной

    void pushBack(const T&); // добавляет в конец массива элемент

    void erase(const T&); // удаляет элемент
    void clear(); // очищает массив

    T &operator[](int); // возвращает ссылку на элемент

    MyVector& operator=(const MyVector<T>& other) {// копирует вектор
        data = new T[other.capacity];
        for(int i = 0; i < other._size; i++)
        {
            data[i] = other.data.get()[i];
        }
        _size = other._size;
        capacity = other.capacity;
        return *this;
    }

};
