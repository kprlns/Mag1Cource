//
// Created by Никита on 01.05.2020.
//

#ifndef NLP_VECTOR_H
#define NLP_VECTOR_H

#include <iostream>

#define VECTOR_DEBUG
#define log(message) do{ std::cout << message << std::endl; }while(0);
#define logCondition(condition, message) do{ \
 if(condition) {std::cout << message << std::endl;}\
} while(0);


template <typename T> class Vector {
public:

    void add(T element);
    void increaseCapacity();
    void resize(int newMaxSize);


    explicit Vector(int size);
    Vector(T* data, int size);
    ~Vector();


    int getSize() {return size;}
    int getMaxSize() {return maxSize;}
    T* getData() {return data;}

    void set(int i, T element);
    T& get(int i) {return data[i];}

    const T& operator[](int i) const;
    T& operator[](int i);

private:
    T* data;
    int maxSize{0};

    ///  Last inserted element index
    int size{0};

    T* allocate(int size);
};



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
    if(size == maxSize) {
        increaseCapacity();
    }
    data[size] = element;
    size++;
}

template<typename T>
void Vector<T>::resize(int newMaxSize) {
    if(newMaxSize == 0) {
        newMaxSize += 1;
    }
    T* newData = allocate(newMaxSize);
    std::copy(data, data + size, newData);
    delete[] data;
    data = newData;
    maxSize = newMaxSize;
}

template<typename T>
void Vector<T>::increaseCapacity() {
    resize(maxSize * 2);
}

template<typename T>
Vector<T>::~Vector() {
    delete [] data;
}

template<typename T>
void Vector<T>::set(int i, T el) {
    if(i >= maxSize) {
        resize(i * 2);
    }
    data[i] = el;
    size = std::max(i + 1, size);
}

template<typename T>
T& Vector<T>::operator[](int i) {
#ifdef VECTOR_DEBUG
    logCondition(i > maxSize, "Warn: Vector out of bounds")
#endif
     return data[i];
}


#endif //NLP_VECTOR_H
