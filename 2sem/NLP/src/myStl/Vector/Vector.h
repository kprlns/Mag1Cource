//
// Created by Никита on 01.05.2020.
//

#ifndef NLP_VECTOR_H
#define NLP_VECTOR_H

#include <iostream>

#define log(message) do{ std::cout << message << std::endl }while(0);


template <typename T> class Vector {
public:

    void add(T element);
    int getSize() { return size; }
    T* getData() { return data; }

    explicit Vector(int size);

    Vector(T* data, int size);


private:
    T* data;
    int maxSize{0};

    ///  Last inserted element index
    int size{0};

    T* allocate(int size);
};



#endif //NLP_VECTOR_H
