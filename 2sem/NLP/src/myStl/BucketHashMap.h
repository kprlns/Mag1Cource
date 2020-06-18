//
// Created by kprlns on 17.06.2020.
//

#ifndef NLP_BUCKETHASHMAP_H
#define NLP_BUCKETHASHMAP_H

#include <climits>

#include "myStl/Vector.h"
#include "myStl/HashMap.h"
#include "myStl/HashSet.h"

template<typename K, typename V>
class BucketHashMap {
public:
    static const int BITS_TO_BUCKET = 16;
    static const int HASH_LENGTH = 64;
    static const int INDEX_INITIAL_SIZE = 100;
    Vector<HashMap<K, V>*>* bucketMap = new Vector<HashMap<K, V>*>(108000);
    int offset;
    int numOfBuckets;

    BucketHashMap() {
        offset = HASH_LENGTH - BITS_TO_BUCKET;
        numOfBuckets = (ULLONG_MAX >> (offset)) + 1;
        bucketMap = new Vector<HashMap<K, V>*>((ULLONG_MAX >> (offset)) + 1);
        for(int i = 0; i < bucketMap->getMaxSize(); ++i) {
            bucketMap->set(i, new HashMap<K, V>(INDEX_INITIAL_SIZE));
        }
    }

    int getBucketIndex(K hash) {
        return (int)(hash >> offset);
    }


    HashMapItem<K, V> get(unsigned long long key) {
        return bucketMap->get(getBucketIndex(key))->get(key);
    }

    HashMapItem<K, V> put(K key, V value) {
        int bucket = (int)(key >> offset);
        return bucketMap->get(bucket)->put(key, value);
    }

    int getSize() {
        int size = 0;
        for(int i = 0; i < bucketMap->getSize(); ++i) {
            size += bucketMap->get(i)->getSize();
        }
        return size;
    }
};


#endif //NLP_BUCKETHASHMAP_H
