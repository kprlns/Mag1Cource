//
// Created by kprlns on 18.06.2020.
//

#ifndef NLP_BUCKETHASHSET_H
#define NLP_BUCKETHASHSET_H


#include <climits>
#include "HashSet.h"

template<typename K>
class BucketHashSet {
public:
    static const int BITS_TO_BUCKET = 16;
    static const int HASH_LENGTH = 64;
    static const int INDEX_INITIAL_SIZE = 100;
    Vector<HashSet<K>*>* bucketSet = new Vector<HashSet<K>*>(108000);
    int offset;
    int numOfBuckets;

    BucketHashSet() {
        offset = HASH_LENGTH - BITS_TO_BUCKET;
        numOfBuckets = (ULLONG_MAX >> (offset)) + 1;
        bucketSet = new Vector<HashSet<K>*>((ULLONG_MAX >> (offset)) + 1);
        for(int i = 0; i < bucketSet->getMaxSize(); ++i) {
            bucketSet->set(i, new HashSet<K>(INDEX_INITIAL_SIZE));
        }
    }

    int getBucketIndex(K hash) {
        return (int)(hash >> offset);
    }


    HashSetItem<K> get(unsigned long long key) {
        return bucketSet->get(getBucketIndex(key))->get(key);
    }

    HashSetItem<K> put(K key) {
        int bucket = (int)(key >> offset);
        return bucketSet->get(bucket)->put(key);
    }

    int getSize() {
        int size = 0;
        for(int i = 0; i < bucketSet->getSize(); ++i) {
            size += bucketSet->get(i)->getSize();
        }
        return size;
    }
};



#endif //NLP_BUCKETHASHSET_H
