//
// Created by kprlns on 16.06.2020.
//

#ifndef NLP_TERMINDEX_H
#define NLP_TERMINDEX_H

#include "myStl/Vector.h"

class TermIndex {
public:

    int count;
    Vector<int>* docIds;
    Vector<int>* frequencies;
    Vector<unsigned char>* flags;
    TermIndex() {}

    TermIndex(int size) {
        count = 0;
        docIds = new Vector<int>(size);
        frequencies = new Vector<int>(size);
        flags = new Vector<unsigned char>(size);
    }
    ~TermIndex() {
        delete docIds;
        delete frequencies;
        delete flags;
    }

    int getSize() {
        return docIds->getSize();
    }

    void add(int docId, int freq) {
        docIds->add(docId);
        frequencies->add(freq);
        count += freq;
    }

    void add(int docId, int freq, unsigned char flag) {
        docIds->add(docId);
        frequencies->add(freq);
        flags->add(flag);
        count += freq;
    }

    void increaseFreqLast(int add) {
        (*frequencies->getPointer(getSize() - 1)) += add;
        count += add;
    }
    int getCount() {
        return count;
    }
    unsigned char isTitle(int i) {
        return TITLE & flags->get(i);
    }
    unsigned char isPresentInFirstFive(int i) {
        return FIRST_FIVE & flags->get(i);
    }
};
#endif //NLP_TERMINDEX_H
