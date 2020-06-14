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
    char* originFilePath;
    char* reverseIndexFilePath;
    char* titleIndexFilePath;
    char* positionFilePath;

    static const int BITS_TO_BUCKET = 16;
    static const int HASH_LENGTH = 64;
    static const int INDEX_INITIAL_SIZE = 100;

    int numOfBuckets;

    Vector<Index*>* indexBuckets;
    Vector<pos_type>* docPositions = new Vector<pos_type>(108000);
    Vector<HashSet<unsigned long long>*>* titleForwardIndex = new Vector<HashSet<unsigned long long>*>(108000);

    int offset;

    int getTotalDocumentsNumber() {
        return docPositions->getSize();
    }
    pos_type getPosition(int docId) {
        return docPositions->get(docId);
    }
    BucketIndex() {
        offset = HASH_LENGTH - BITS_TO_BUCKET;
        numOfBuckets = (ULLONG_MAX >> (offset)) + 1;
        indexBuckets = new Vector<Index*>((ULLONG_MAX >> (offset)) + 1);
        for(int i = 0; i < indexBuckets->getMaxSize(); ++i) {
            indexBuckets->set(i, new Index(INDEX_INITIAL_SIZE));
        }

    }
    ~BucketIndex() {
        indexBuckets->deleteAll();
        titleForwardIndex->deleteAll();
        delete titleForwardIndex;
        delete indexBuckets;
    }

    void putTitleForwardIndex(HashSet<unsigned long long>* titleIndex) {
        titleForwardIndex->add(titleIndex);
    }

    void putAll(HashSet<unsigned long long>* allHashes, int docId, pos_type docPosition) {
        for(int i = 0; i < allHashes->getSize(); ++i) {
            putOne(allHashes->getAtPos(i), docId);
        }
        docPositions->add(docPosition);
    }

    int getBucketIndex(unsigned long long hash) {
        return (int)(hash >> offset);
    }

    void putOne(unsigned long long hash, int docId) {
        int bucket = (int)(hash >> offset);
        indexBuckets->get(bucket)->putOne(hash, docId);
    }

    HashMapItem<unsigned long long, Vector<int>*> get(unsigned long long hash) {
        return indexBuckets->get(getBucketIndex(hash))->get(hash);
    }

    void printIndex() {
        for(int i = 0; i < indexBuckets->getSize(); ++i) {
            indexBuckets->get(i)->printIndex();
        }
    }
    void printPositions() {
        std::wcout << L"\n----------------------\n";
        for(int i = 0; i < docPositions->getSize(); ++i) {
            std::wcout << docPositions->get(i) << " ";
        }
        std::wcout << std::endl;
    }
    void printForwardIndex() {
        std::wcout << L"\n========================\n";
        for(int i = 0; i < titleForwardIndex->getSize(); ++i) {
            std::wcout << i << L" : ";
            auto current = titleForwardIndex->get(i);
            for(int j = 0; j < current->getSize(); j++) {
                std::wcout << current->getAtPos(j) << L" ";
            }
            std::wcout << std::endl;
        }
    }
    void printAll() {
        printIndex();
        printPositions();
        printForwardIndex();
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
