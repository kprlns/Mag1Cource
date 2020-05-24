//
// Created by Никита on 02.05.2020.
//

#ifndef NLP_STRING_H
#define NLP_STRING_H

#include <ostream>

#include <locale>
#include "myStl/Vector/Vector.h"


// std::char_traits<char>::length(str)

template <typename T> class String {
public:
    String() {}//string = Vector<T>(128);
    String(int size) : string(size) {}//string = Vector<T>(128);
    explicit String(const T* str) : string(std::char_traits<T>::length(str)) {
        int size = string.getMaxSize();
        string.addAll(str, size);
    }
    String(const T* str, int size) : string(size) {
        int sz = string.getMaxSize();
        string.addAll(str, sz);
    }
    String(String<T>& other)
    : string(other.string){ std::cout << "String&" << std::endl;}
    String(String<T>&& other)  noexcept
    : string(other.string){ std::cout << "String&&" << std::endl;}

    constexpr String<T>& operator=(const String<T>& other) noexcept {
        std::cout << "String&=" << std::endl;
        this->string = other.string;
        return *this;
    }
    constexpr String<T>& operator=(String<T>&& other) noexcept {
        std::cout << "String&&=" << std::endl;
        this->string = std::move(other.string);
        return *this;
    }


    int getSize() const;
    int getMaxSize() const;
    unsigned long long hashCode();

    bool operator==(String<T>& other) const;
    bool operator==(String<T>&& other) const;
    bool operator==(const T* other) const;

    void trim();

    String<T> operator+(String<T>& other);
    const T& operator[](int i) const;
    bool operator<(String<T>& other);

    template<typename C> friend std::ostream& operator<<(std::ostream& out, const String<C>& obj);
    template<typename C> friend std::wostream & operator<<(std::wostream & out, const String<C>& obj);

    void print();


    void add(T el);
    String<T> substring(int start, int end);
    Vector<String<T>> split(T splitter);

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
std::ostream & operator<<(std::ostream& out, const String<C>& str) {
    for(int i = 0; i < str.getSize(); ++i) {
        out << str[i];
    }
    return out;
}

template<typename C>
std::wostream& operator<<(std::wostream & out, const String<C>& str) {
    for(int i = 0; i < str.getSize(); ++i) {
        out << str[i];
    }
    return out;
}

template<typename T>
void String<T>::print() {
    for(int i = 0; i < getSize(); ++i) {
        std::wcout << (T)string.get(i);
    }
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
int String<T>::getMaxSize() const {
    return string.getMaxSize();
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
Vector<String<T>> String<T>::split(T splitter) {
    Vector result = Vector<String<T>>(32);
    int start = 0;
    int end = 0;
    for(int i = 0; i < getSize(); ++i) {
        char a = string[i];
        if(string[i] != splitter) {
            end++;
        }
        else {
            if(start < end) {
                //std::cout << "!!!" << substring(start, end) << std::endl;
                //std::cout << start << "  " << end << std::endl;
                result.add(std::move(substring(start, end)));
            }
            end = i + 1;
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
