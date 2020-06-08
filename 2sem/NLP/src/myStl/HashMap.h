//
// Created by kprlns on 08.06.2020.
//

#ifndef NLP_HASHMAP_H
#define NLP_HASHMAP_H

#include "myStl/Vector.h"
#include "myStl/Pair.h"

template <typename K, typename V>
class HashMapItem {
public:
    HashMapItem() = default;
    bool found{};
    Pair<K,V>* item;
};


template <typename K, typename V> class HashMap {
private:
    Vector<Pair<K,V>*>* set;

public:
    //Returns position to insert if not exists otherwise position
    int binarySearch(const K &key, int *positionToInsert) {
        //std::wcout << "\n-----------" << key << "----------------\n";
        int start = 0;
        int end = set->getSize() - 1;
        int mid;
        while (start <= end) {
            mid = start + (end - start) / 2;
            //std::wcout << "[ " << start << "  " << end << " ]\n";

            if (set->get(mid)->key == key) {
                return mid;
            }

            if (set->get(mid)->key < key) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        //std::wcout << "{ " << start << "  " << end << " }\n";
        (*positionToInsert) = start;
        return -1;
    }

    explicit HashMap(int size) {
        set = new Vector<Pair<K, V>*>(size);
    }

    explicit HashMap(Vector<Pair<K, V>*> set) {
        this->set = set;
    }
    void deleteAll() {
        //for(int i = 0; i < set->getSize(); ++i) {
        //    delete set->get(i);
        //}
        set->deleteAll();
    }

    ~HashMap() {
        deleteAll();
        delete set;
    }

    HashMapItem<K,V> get(const K &key) {
        int posToInsert = -1;
        //return binarySearch(key, posToInsert);
        HashMapItem<K,V> result;
        int res = binarySearch(key, &posToInsert);
        if (res == -1) {
            result.found = false;
        } else {
            result.found = true;
            result.item = set->get(res);
        }
        return result;
    }

    HashMapItem<K,V> put(const K &key, const V& value) {
        int posToInsert = -1;
        HashMapItem<K,V> result;
        result.found = true;
        int res = binarySearch(key, &posToInsert);
        if (res == -1) {

            set->insertAt(posToInsert, new Pair<K, V>(key, value));
            result.item = set->get(posToInsert);
            return result;
        } else {
            result.item = set->get(res);
        }
        return result;

    }

    int getSize() {
        return set->getSize();
    }

    Pair<K,V>* getAtPos(int i) {
        return set->get(i);
    }

};

/*






 */



#endif //NLP_HASHMAP_H
