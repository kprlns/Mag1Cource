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
    Vector<HashMap<unsigned long long, int>*>* forwardIndex = new Vector<HashMap<unsigned long long, int>*>(108000);
    Vector<int>* docSizes = new Vector<int>(108000);
    //Vector<Vector<int>*>* frequencies = new Vector<Vector<int>*>(108000);
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
        //for(int i = 0; i < frequencies->getSize(); ++i) {
        //    frequencies->set(i, new Vector<int>(64));
        //}
    }
    ~BucketIndex() {
        delete docPositions;
        indexBuckets->deleteAll();
        forwardIndex->deleteAll();
        delete forwardIndex;
        delete indexBuckets;
    }

    void putTitleForwardIndex(Vector<unsigned long long>* forward) {
        auto* currentForwardIndex = new HashMap<unsigned long long, int>(128);
        //forwardIndex->add(titleIndex);
        for(int i = 0; i < forward->getSize(); ++i) {
            HashMapItem<unsigned long long, int> inserted =
                    currentForwardIndex->put(forward->get(i), 0);
            inserted.item->value += 1;
        }
        forwardIndex->add(currentForwardIndex);
    }

    void putAll(HashSet<unsigned long long>* allHashes, int docId, pos_type docPosition) {
        for(int i = 0; i < allHashes->getSize(); ++i) {
            putOne(allHashes->getAtPos(i), docId);
        }
        docPositions->add(docPosition);
    }
    void putAllVector(Vector<unsigned long long>* allHashes, int docId, pos_type docPosition) {
        for(int i = 0; i < allHashes->getSize(); ++i) {
            putOne(allHashes->get(i), docId);
        }
        docSizes->add(allHashes->getSize());
        docPositions->add(docPosition);
    }
    void putAllVectorWithStats(Vector<unsigned long long>* allHashes, int docId, pos_type docPosition) {
        for(int i = 0; i < allHashes->getSize(); ++i) {
            putOne(allHashes->get(i), docId);
        }
        docSizes->add(allHashes->getSize());
        docPositions->add(docPosition);
    }

    int getBucketIndex(unsigned long long hash) {
        return (int)(hash >> offset);
    }

    void putOne(unsigned long long hash, int docId) {
        int bucket = (int)(hash >> offset);
        indexBuckets->get(bucket)->putOne(hash, docId);
    }

    void putOneWithFrequencies(unsigned long long hash, int docId) {
        int bucket = (int)(hash >> offset);
        auto hashSetItem = indexBuckets->get(bucket)->putOne(hash, docId);

        //Vector<int>* freqBucket = frequencies->get(bucket);
        //if(freqBucket->getSize() < hashSetItem.item->value->getSize()) {
        //    freqBucket->insertAt(hashSetItem.position)
        //}
    }

    HashMapItem<unsigned long long, TermIndex*> get(unsigned long long hash) {
        return indexBuckets->get(getBucketIndex(hash))->get(hash);
    }

    void printIndex() {
        for(int i = 0; i < indexBuckets->getSize(); ++i) {
            indexBuckets->get(i)->printIndexWithFreq();
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
        for(int i = 0; i < forwardIndex->getSize(); ++i) {
            std::wcout << i << L" : ";
            auto current = forwardIndex->get(i);
            for(int j = 0; j < current->getSize(); j++) {
                std::wcout << L"{" << current->getAtPos(j)->key << L", " << current->getAtPos(j)->value << L"} ";
            }
            std::wcout << std::endl;
        }
        std::wcout << L"Sizes: \n";
        for(int i = 0; i < docSizes->getSize(); ++i) {
            std::wcout << docSizes->get(i) << L" ";
        }
        std::wcout << std::endl;

    }
    void printAll() {
        printIndex();
        printForwardIndex();
        printPositions();
    }

    int getSize() {
        int size = 0;
        for(int i = 0; i < indexBuckets->getSize(); ++i) {
            size += indexBuckets->get(i)->index->getSize();
        }
        return size;
    }

    bool equals(BucketIndex* other) {
        return equalsPos(other) && equalsForwardIndex(other) && equalsIndex(other);
    }
    bool equalsPos(BucketIndex* other) {
        return *this->docPositions == *other->docPositions;
    }
    bool equalsForwardIndex(BucketIndex* other) {
        auto firstIndex = forwardIndex;
        auto secondIndex = other->forwardIndex;
        if(firstIndex->getSize() != secondIndex->getSize()) {
            return false;
        }
        for(int i = 0; i < firstIndex->getSize(); ++i) {
            auto firstMap = firstIndex->get(i);
            auto secondMap = secondIndex->get(i);
            if(firstMap->getSize() != secondMap->getSize()) {
                return false;
            }
            for(int j = 0; j < firstMap->getSize(); ++j) {
                auto firstEl = firstMap->getAtPos(j);
                auto secondEl = secondMap->getAtPos(j);
                if(!((firstEl->key == secondEl->key) && (firstEl->value == secondEl->value))) {
                    return false;
                }
            }
        }
        return true;
    }
    bool equalsIndex(BucketIndex* other) {
        auto firstIndex = indexBuckets;
        auto secondIndex = other->indexBuckets;
        if(firstIndex->getSize() != secondIndex->getSize()) {
            return false;
        }
        for(int i = 0; i < firstIndex->getSize(); ++i) {
            auto firstMap = firstIndex->get(i)->index;
            auto secondMap = secondIndex->get(i)->index;
            if(firstMap->getSize() != secondMap->getSize()) {
                return false;
            }
            for(int j = 0; j < firstMap->getSize(); ++j) {
                auto firstEl = firstMap->getAtPos(j);
                auto secondEl = secondMap->getAtPos(j);
                if((firstEl->getKey() != secondEl->getKey())
                || (firstEl->getValue()->getSize() != secondEl->getValue()->getSize())
                || (firstEl->getValue()->count != secondEl->getValue()->count))
                {
                    return false;
                }

                for(int k = 0; k < firstEl->getValue()->getSize(); ++k) {
                    if(! ((firstEl->value->docIds->get(k) == firstEl->value->docIds->get(k))
                    && (firstEl->value->frequencies->get(k) == firstEl->value->frequencies->get(k)))) {
                        return false;
                    }
                }
            }

        }
        return true;
    }
};




#endif //NLP_BUCKETINDEX_H
