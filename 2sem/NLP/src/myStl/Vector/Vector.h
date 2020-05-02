//
// Created by Никита on 01.05.2020.
//

#ifndef NLP_VECTOR_H
#define NLP_VECTOR_H

template <typename T> class Vector {
public:
    T el;

    int getSize() { return size; }

    Vector() {
        size = 11;
    }
    Vector(T type) {
        size = 10;
        el = type;
    }


private:
    int size;
};

#endif //NLP_VECTOR_H
