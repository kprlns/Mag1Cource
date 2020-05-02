//
// Created by Никита on 01.05.2020.
//

#include "Vector.h"


template<typename T>
Vector<T>::Vector(int size) {
    this->size = 0;
    this->maxSize = size;
    this->data = allocate(size);
}

template<typename T>
Vector<T>::Vector(T* data, int size) {
    this->maxSize = size;
    std::copy(data, data + size, this->data);
}

template<typename T>
T* Vector<T>::allocate(int size) {
    return new T[size];
}

template<typename T>
void Vector<T>::add(T element) {
    data[size] = element;
    size++;
}
