//
// Created by Никита on 02.05.2020.
//

#ifndef NLP_STRING_H
#define NLP_STRING_H

#include <ostream>

#include <locale>
#include "Vector.h"


// std::char_traits<char>::length(str)

template <typename T> class String {
public:
    String() {}//string = Vector<T>(128);
    String(int size) : string(size) {}//string = Vector<T>(128);
    explicit String(const T* str) : string(wcslen(str)) {
        int size = string.getMaxSize();
        string.addAll(str, size);
    }
    String(const T* str, int size) : string(size) {
        int sz = string.getMaxSize();
        string.addAll(str, sz);
    }
    String(String<T>& other) : string(other.string) {
#ifdef DEBUG_CONSTRUCTOR
        std::cout << "String&" << std::endl;
#endif
        hash = other.hash;
        isHashRelevant = other.isHashRelevant;
    }
    String(String<T>&& other)  noexcept : string(other.string){
#ifdef DEBUG_CONSTRUCTOR
        std::cout << "String&&" << std::endl;
#endif
        hash = other.hash;
        isHashRelevant = other.isHashRelevant;
    }

    constexpr String<T>& operator=(const String<T>& other) noexcept {
#ifdef DEBUG_CONSTRUCTOR
        std::cout << "String&=" << std::endl;
#endif
        this->string = other.string;
        hash = other.hash;
        isHashRelevant = other.isHashRelevant;
        return *this;
    }
    constexpr String<T>& operator=(String<T>&& other) noexcept {
#ifdef DEBUG_CONSTRUCTOR
        std::cout << "String&&=" << std::endl;
#endif
        this->string = std::move(other.string);
        hash = other.hash;
        isHashRelevant = other.isHashRelevant;
        return *this;
    }


    int getSize() const;
    int getMaxSize() const;
    unsigned long long hashCode();

    bool operator==(String<T>& other) const;
    bool operator==(String<T>&& other) const;
    bool operator==(const T* other) const;
    bool contains(T pattern);
    void trim();

    String<T> operator+(String<T>& other);
    const T& operator[](int i) const;
    bool operator<(String<T>& other);

    template<typename C> friend std::ostream& operator<<(std::ostream& out, const String<C>& obj);
    template<typename C> friend std::wostream & operator<<(std::wostream & out, const String<C>& obj);

    void print();

    void set(int i, T val) {
        isHashRelevant = false;
        string.set(i, val);
    }
    T get(int i) {
        return string[i];
    }
    void add(T el);
    String<T>* substring(int start, int end);
    Vector<String<T>*>* split(T splitter);
    Vector<String<T>*>* splitIfContains(T splitter);

private:
    Vector<T> string;
    bool isHashRelevant = false;
    unsigned long long hash = 0;
    //Should be simple
    static const unsigned long long HASH_BASE = 37;
    static const wchar_t START_SYMBOL = L'а';


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
Vector< String<T>* >* String<T>::split(T splitter) {
    auto result = new Vector< String<T>* >(32);
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
                result->add(substring(start, end));
            }
            end = i + 1;
            start = i + 1;
            continue;
        }
    }
    if(start < end) {
        result->add(substring(start, end));
    }
    return result;
}

template<typename T>
Vector< String<T>* >* String<T>::splitIfContains(T splitter) {
    if(contains(splitter)) {
        return split(splitter);
    }
    return nullptr;
}


template<typename T>
String<T>* String<T>::substring(int start, int end) {
    auto* result = new String(0);
    result->string.swap(string.getInterval(start, end));
    return result;
}

template<typename T>
bool String<T>::contains(T pattern) {
    for(int i = 0; i < getSize(); ++i) {
        if(string[i] == pattern) {
            return true;
        }
    }
    return false;
}

#endif //NLP_STRING_H
