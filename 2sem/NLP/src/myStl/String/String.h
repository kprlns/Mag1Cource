//
// Created by Никита on 02.05.2020.
//

#ifndef NLP_STRING_H
#define NLP_STRING_H

#include <ostream>

#include "myStl/Vector/Vector.h"
// std::char_traits<char>::length(str)

template <typename T> class String {
public:
    String();
    String(int size);
    explicit String(const T* str);

    int getSize() const;
    unsigned long long hashCode();

    bool operator==(String<T>& other);
    bool operator==(String<T>&& other);
    bool operator==(const T* other);

    String<T> operator+(String<T>& other);
    const T& operator[](int i) const;
    bool operator<(String<T>& other);

    template<typename C> friend std::ostream& operator<<(std::ostream& out, const String<C>& obj);


    void add(T el);
private:
    Vector<T> string;
    bool isHashRelevant = false;
    unsigned long long hash = 0;
    //Should be simple
    const unsigned long long HASH_BASE = 37;
    const wchar_t START_SYMBOL = 'a';


    bool compare(const T* other, int otherSize);
};

template<typename T>
String<T>::String() : string(128) {
    //string = Vector<T>(128);
}
template<typename T>
String<T>::String(int size) : string(size) {
    //string = Vector<T>(128);
}
template<typename T>
String<T>::String(const T* str) : string(std::char_traits<T>::length(str)) {
    int size = string.getMaxSize();
    //string = Vector<T>(size);
    string.addAll(str, size);
}

template<typename T>
bool String<T>::operator==(String<T>& other) {
    return compare(other.string, other.string.getSize());
}
template<typename T>
bool String<T>::operator==(String<T>&& other) {
    return compare(other.string, other.string.getSize());
}
template<typename T>
bool String<T>::operator==(const T* other) {
    int otherSize = std::char_traits<T>::length(other);
    return compare(other, otherSize);
}


template<typename T>
bool String<T>::compare(const T* other, int otherSize) {
    if(string.getSize() != otherSize) {
        return false;
    }
    for(int i = 0; i < string.getSize(); ++i) {
        if(string.get(i) != other[i]) {
            return false;
        }
    }
    return true;
}

template<typename T>
const T& String<T>::operator[](int i) const{
    return string.get(i);
}

template<typename T>
String<T> String<T>::operator+(String<T>& other) {
    String<T> result(this->getSize() + other.getSize());
    //std::copy(this->string.getData(), this->string.getData() + this->getSize(), result.string.getData());
    //std::copy(other.string.getData(), other.string.getData() + other.getSize(), result.string.getData() + this->getSize());
    result.string.addAll(this->string);
    result.string.addAll(other.string);
    return result;
}

template<typename C>
std::ostream& operator<<(std::ostream& out, const String<C>& str) {
    for(int i = 0; i < str.getSize(); ++i) {
        out << str[i];
    }
    return out;
}

template<typename T>
bool String<T>::operator<(String<T>& other) {
    return false;
}

template<typename T>
int String<T>::getSize() const {
    return string.getSize();
}

template<typename T>
void String<T>::add(T el) {
    string.add(el);
    isHashRelevant = false;
}

template<typename T>
unsigned long long String<T>::hashCode() {
    if(isHashRelevant) {
        return hash;
    }
    hash = 0;
    unsigned long long pow = HASH_BASE;
    for(int i = 0; i < getSize(); ++i) {
        hash += (this[i] - START_SYMBOL + 1) * pow;
        pow *= HASH_BASE;
    }
    isHashRelevant = true;
    return hash;
}



#endif //NLP_STRING_H
