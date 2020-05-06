//
// Created by Никита on 02.05.2020.
//

#ifndef NLP_STRING_H
#define NLP_STRING_H

#include <ostream>

#include "locale"
#include "myStl/Vector/Vector.h"
// std::char_traits<char>::length(str)

template <typename T> class String {
public:
    String();
    String(int size);
    explicit String(const T* str);
    String(String<T>& other);

    int getSize() const;
    unsigned long long hashCode();

    bool operator==(String<T>& other) const;
    bool operator==(String<T>&& other) const;
    bool operator==(const T* other) const;

    void trim();

    String<T> operator+(String<T>& other);
    const T& operator[](int i) const;
    bool operator<(String<T>& other);

    template<typename C> friend std::ostream& operator<<(std::ostream& out, const String<C>& obj);


    void add(T el);
    String<T> substring(int start, int end);
    Vector<String<T>> split(T c);

private:
    Vector<T> string;
    bool isHashRelevant = false;
    unsigned long long hash = 0;
    //Should be simple
    static const unsigned long long HASH_BASE = 37;
    static const wchar_t START_SYMBOL = 'a';


    bool compare(const T* other, int otherSize) const;
};

template<typename T>
String<T>::String(String<T>& other) : string(other.string){}

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
bool String<T>::operator==(String<T>& other) const {
    return compare(other.string, other.string.getSize());
}
template<typename T>
bool String<T>::operator==(String<T>&& other) const {
    return compare(other.string, other.string.getSize());
}
template<typename T>
bool String<T>::operator==(const T* other) const {
    int otherSize = std::char_traits<T>::length(other);
    return compare(other, otherSize);
}


template<typename T>
bool String<T>::compare(const T* other, int otherSize) const {
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

template<typename T>
void String<T>::trim() {
    int start = 0;
    int end = getSize();
    while(isspace(string[start]) && start < (end - 1)) {
        start++;
    }
    while(isspace(string[end - 1]) && start < (end - 1)) {
        end--;
    }
    string.swap(string.getInterval(start, end));
}

template<typename T>
Vector<String<T>> String<T>::split(T c) {
    Vector result = Vector<String<T>>(32);
    int start = 0;
    int end = 0;
    for(int i = 0; i < getSize(); ++i) {
        end++;
        if(string[i] == c) {
            if(start < end) {
                std::cout << "!!!" << substring(start, end) << std::endl;
                std::cout << start << "  " << end << std::endl;
                result.add(substring(start, end));
            }
            end = i;
            start = i + 1;
            continue;
        }
    }
    if(start < end) {
        result.add(substring(start, end));
    }
    return result;
}

template<typename T>
String<T> String<T>::substring(int start, int end) {
    String<T> result(0);
    result.string.swap(string.getInterval(start, end));
    return result;
}




#endif //NLP_STRING_H
