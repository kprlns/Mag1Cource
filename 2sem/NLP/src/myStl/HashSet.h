//
// Created by kprlns on 05.06.2020.
//

#ifndef NLP_HASHSET_H
#define NLP_HASHSET_H


#include "myStl/Vector.h"


template <typename T> class HashSet {
private:
    Vector<T>* set;

public:
    //Returns position to insert if not exists otherwise position
    int binarySearch(const T& key, int* positionToInsert) {
        std::wcout << "\n-----------" << key << "----------------\n";
        int start = 0;
        int end = set->getSize() - 1;
        int mid;
        while (start <= end) {
            mid = start + (end - start) / 2;
            std::wcout << "[ " << start << "  " << end << " ]\n";

            if(set->get(mid) == key) {
                return mid;
            }

            if(set->get(mid) < key) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        std::wcout << "{ " << start << "  " << end << " }\n";
        (*positionToInsert) = start;
        return -1;
    }




    explicit HashSet(int size) {
        set = new Vector<T>(size);
    }
    explicit HashSet(Vector<T>* set) {
        this->set = set;
    }
    void deleteAll() {
        for(int i = 0; i < set->getSize(); ++i) {
            delete set->get(i);
        }
    }
    ~HashSet() {
        delete set;
    }

    T get(const T& key) {
        int posToInsert = -1;
        //return binarySearch(key, posToInsert);
        int res = binarySearch(key, posToInsert);
        if (res == -1) {
            return nullptr;
        } else {
            return set[res];
        }
    }

    T put(const T& key) {
        int posToInsert = -1;
        int res = binarySearch(key, posToInsert);
        if (res == -1) {
            set->insertAt(posToInsert, key);
        }
        return set[posToInsert];
    }


};

#endif //NLP_HASHSET_H

