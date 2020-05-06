//
// Created by Никита on 01.05.2020.
//

#ifndef NLP_VECTOR_H
#define NLP_VECTOR_H

#include <iostream>
#include <cstring>

#define VECTOR_DEBUG
#define log(message) do{ std::cout << message << std::endl; }while(0);

#define logCondition(condition, message) do{ \
 if(condition) {std::cout << message << std::endl;}\
} while(0);




template <typename T> class Vector {
public:

    void add(const T& element);
    void addAll(Vector<T>& other);
    void addAll(const T* array, int arraySize);
    bool operator==(Vector<T>& other);
    bool operator==(Vector<T>&& other);

    void increaseCapacity();
    void increaseCapacity(int minSize);

    void resize(int newMaxSize);

    explicit Vector(int size);
    Vector(Vector<T>& other);
    //Vector(Vector<T>&& other);
    Vector(T* data, int size);
    ~Vector();


    int getSize() const;
    int getMaxSize() {return maxSize;}
    T* getData() {return data;}

    void set(int i, T element);
    T& get(int i) const {return data[i];};
    const T& operator[](int i);

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
Vector<T>::Vector(Vector<T>& other) {
    std::cout << "T&\n";
    this->size = other.size;
    this->maxSize = other.maxSize;
    this->data = allocate(maxSize);
    std::copy(other.data, other.data + size, data);
}

/*template<typename T>
Vector<T>::Vector(Vector<T>&& other) {
    std::cout << "T&&\n";
    this->size = other.size;
    this->maxSize = other.maxSize;
    this->data = other.data;
    //this->data = allocate(maxSize);
    //std::copy(other.data, other.data + size, data);
}*/


template<typename T>
T* Vector<T>::allocate(int size) {
    T* array = new T[size];
    std::memset(array, 0, size * sizeof(T));
    return array;
}

template<typename T>
void Vector<T>::add(const T& element) {
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
void Vector<T>::increaseCapacity(int minSize) {
    while(maxSize < minSize) {
        if(!maxSize) { maxSize++; }
        maxSize *= 2;
    }
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
const T& Vector<T>::operator[](int i) {
#ifdef VECTOR_DEBUG
    logCondition(i > maxSize, "Error: Vector out of bounds")
    logCondition(i > size, "Warn: trying to get element [i > size]")
#endif
     return data[i];
}

template<typename T>
void Vector<T>::addAll(Vector<T>& other) {
    this->addAll(other.data, other.size);
}

template<typename T>
void Vector<T>::addAll(const T* array, int arraySize) {
    while(size + arraySize > maxSize) {
        increaseCapacity(size + arraySize);
    }
    std::copy(array, array + arraySize, data + size);
    size += arraySize;
}

template<typename T>
bool Vector<T>::operator==(Vector<T>& other) {
    if(this->maxSize != other.maxSize) {
        return false;
    }
    for(int i = 0; i < maxSize; ++i) {
        if(this->get(i) != other.get(i)) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Vector<T>::operator==(Vector<T>&& other) {
    if(this->maxSize != other.maxSize) {
        return false;
    }
    for(int i = 0; i < maxSize; ++i) {
        if(this->get(i) != other.get(i)) {
            return false;
        }
    }
    return true;
}

template<typename T>
int Vector<T>::getSize() const {
    return size;
}


#endif //NLP_VECTOR_H
