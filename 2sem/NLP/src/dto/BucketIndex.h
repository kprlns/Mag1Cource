//
// Created by kprlns on 08.06.2020.
//

#ifndef NLP_BUCKETINDEX_H
#define NLP_BUCKETINDEX_H

#include <climits>

#include "Common.h"
#include "index/Index.h"
#include "myStl/Vector.h"

class BucketIndex {

public:
    static const int BITS_TO_BUCKET = 16;
    static const int HASH_LENGTH = 64;
    static const int INDEX_INITIAL_SIZE = 500;

    Vector<Index*>* indexBuckets;
    Vector<pos_type>* docPositions = new Vector<pos_type>(108000);

    int offset;
    BucketIndex() {
        offset = HASH_LENGTH - BITS_TO_BUCKET;
        indexBuckets = new Vector<Index*>((ULLONG_MAX >> (offset)) + 1);
        for(int i = 0; i < indexBuckets->getMaxSize(); ++i) {
            indexBuckets->set(i, new Index(INDEX_INITIAL_SIZE));
        }

    }
    ~BucketIndex() {
        indexBuckets->deleteAll();
        delete indexBuckets;
    }

    void putAll(HashSet<unsigned long long>* allHashes, int docId, pos_type docPosition) {
        for(int i = 0; i < allHashes->getSize(); ++i) {
            putOne(allHashes->getAtPos(i), docId);
        }
        docPositions->add(docPosition);
    }

    void putOne(unsigned long long hash, int docId) {
        int bucket = (int)(hash >> offset);
        indexBuckets->get(bucket)->putOne(hash, docId);
    }

    void printIndex() {
        for(int i = 0; i < indexBuckets->getSize(); ++i) {
            indexBuckets->get(i)->printIndex();
        }
    }
    void printPositions() {
        std::wcout << "\n----------------------\n";
        for(int i = 0; i < docPositions->getSize(); ++i) {
            std::wcout << docPositions->get(i) << " ";
        }
        std::wcout << std::endl;
    }

    int getSize() {
        int size = 0;
        for(int i = 0; i < indexBuckets->getSize(); ++i) {
            size += indexBuckets->get(i)->index->getSize();
        }
        return size;
    }
};




#endif //NLP_BUCKETINDEX_H
