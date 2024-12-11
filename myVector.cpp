#include "myVector.h"

template<typename T>
void MyVector<T>::deleteNode(int index)
{
    auto temp = new T[capacity];
    int newIndex = 0;
    for (int i = 0; i < _size; i++) {
        if (index != i)
            temp[newIndex++] = data[i];
    }
    data = std::move(temp);
}

template<typename T>
int MyVector<T>::find(const T &toFind)
{
    for (int i = 0; i < _size; i++) {
        if (data[i] == toFind) {
            return i;
        }
    }
    return -1;
}

template<typename T>
MyVector<T>::MyVector()
{
    data = nullptr;
    _size = 0;
    capacity = 0;
}


template<typename T>
MyVector<T>::~MyVector()
{
    delete data;
    _size = 0;
    capacity = 0;
}

template<typename T>
int MyVector<T>::size() {
    return _size;
}

template<typename T>
bool MyVector<T>::indexIsCorrect(int i)
{
    return i >= 0 && i < _size;
}

template<typename T>
bool MyVector<T>::contains(const T &other)
{
        return !(find(other) == -1);
}

template<typename T>
void MyVector<T>::resize(int newSize)
{
        data = (new T[newSize]);
        _size = newSize;
        capacity = newSize;
}

template<typename T>
void MyVector<T>::pushBack(const T &value)
{
        if (capacity == _size) {
        T* tmpValue = new T[_size + 1];
        for (int i = 0; i < capacity; i++) {
            tmpValue[i] = data[i];
        }
        data = std::move(tmpValue);
        capacity = _size + 1;
        }

        data[_size] = value;
        _size++;
}

template<typename T>
void MyVector<T>::erase(const T &toFind)
{
        int index = find(toFind);
        if (index != -1) {
        deleteNode(index);
        _size--;
        }
}

template<typename T>
void MyVector<T>::clear()
{
        _size = 0;
        delete data;
        capacity = 0;
}

template<typename T>
T &MyVector<T>::operator[](int index)
{
        if (!indexIsCorrect(index))
            throw std::exception();
        return data[index];
}
