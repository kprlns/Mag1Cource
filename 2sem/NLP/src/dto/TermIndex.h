//
// Created by kprlns on 16.06.2020.
//

#ifndef NLP_TERMINDEX_H
#define NLP_TERMINDEX_H

#include "myStl/Vector.h"

class TermIndex {
public:
    //TODO add sum of frequencies
    TermIndex(int size) {
        docIds = new Vector<int>(size);
        frequencies = new Vector<int>(size);
    }
    ~TermIndex() {
        delete docIds;
        delete frequencies;
    }

    int getSize() {
        return docIds->getSize();
    }

    void add(int docId, int freq) {
        docIds->add(docId);
        frequencies->add(freq);
    }

    void increaseFreqLast(int add) {
        (*frequencies->getPointer(getSize() - 1)) += add;
    }

    Vector<int>* docIds;
    Vector<int>* frequencies;

};
#endif //NLP_TERMINDEX_H
