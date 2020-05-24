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
    explicit Vector(int size)  {
        this->size = 0;
        this->maxSize = size;
        this->data = allocate(size);
    }
    Vector() {}
    Vector(Vector<T>& other)  {
        std::cout << "Vector&" << std::endl;
        this->size = other.size;
        this->maxSize = other.maxSize;
        this->data = allocate(maxSize);
        std::copy(other.data, other.data + size, data);
    }
    Vector(T* data, int size) {
        this->maxSize = size;
        std::copy(data, data + size, this->data);
    }
    Vector(Vector<T>&& other)  {
        std::cout << "Vector&&" << std::endl;
        this->size = other.size;
        this->maxSize = other.maxSize;
        this->data = other.data;

        other.data = nullptr;
        //this->data = allocate(maxSize);
        //std::copy(other.data, other.data + size, data);
    }
    ~Vector() {
        if(data != nullptr) {
            delete[] data;
        }
    }
    Vector<T>& operator=(const Vector<T>& other) noexcept {
        if(this == &other) { return *this; }
        std::cout << "Vector&=" << std::endl;
        delete data;
        this->size = other.size;
        this->maxSize = other.maxSize;
        data = allocate(maxSize);
        std::copy(other.data, other.data + size, data);
        return *this;
    }
    Vector<T>& operator=(Vector<T>&& other) noexcept {
        std::cout << "Vector&&=" << std::endl;
        this->data = other.data;
        other.data = nullptr;
        this->maxSize = other.maxSize;
        this->size = other.size;
        return *this;
    }

    void add(const T& element);
    void add(T&& element);
    void addAll(Vector<T>& other);
    void addAll(const T* array, int arraySize);
    void remove(int i);

    bool operator==(Vector<T>& other);
    bool operator==(Vector<T>&& other);

    void increaseCapacity();
    void increaseCapacity(int minSize);

    void resize(int newMaxSize);




    int getSize() const;
    int getMaxSize() {return maxSize;}
    T* getData() {return data;}
    Vector<T> getInterval(int start, int end);

    void set(int i, T element);
    T& get(int i) const {return data[i];};
    const T& operator[](int i);

    void swap(Vector<T>&& other);
private:
    T* data;
    int maxSize{0};

    ///  Last inserted element index
    int size{0};

    T* allocate(int size);
};

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
void Vector<T>::add(T&& element) {
    if(size == maxSize) {
        increaseCapacity();
    }
    data[size] = std::move(element);
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
    if(this->size != other.size) {
        return false;
    }
    for(int i = 0; i < size; ++i) {
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

/// Makes interval [start, end) from vector
template<typename T>
Vector<T> Vector<T>::getInterval(int start, int end) {
    int size = end - start;
    Vector<T> result(size);
    std::copy(data + start, data + end, result.data);
    result.size = size;
    return std::move(result);
}

template<typename T>
void Vector<T>::remove(int i) {
#ifdef VECTOR_DEBUG
    logCondition(i >= maxSize, "Error: Vector out of bounds")
    logCondition(i >= size, "Warn: trying to remove element [i > size]")
#endif
    if(i == maxSize - 1) {
        size--;
        return;
    }
    std::copy(data + i + 1, data + size, data + i);
    size--;
}

template<typename T>
void Vector<T>::swap(Vector<T>&& other) {
    T* tmp = this->data;
    this->data = other.data;
    other.data = tmp;

    int tmpSize = this->size;
    this->size = other.size;
    other.size = tmpSize;

    tmpSize = this->maxSize;
    this->maxSize = other.maxSize;
    other.maxSize = tmpSize;
}



#endif //NLP_VECTOR_H
