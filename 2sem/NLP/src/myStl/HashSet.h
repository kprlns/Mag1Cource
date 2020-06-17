//
// Created by kprlns on 05.06.2020.
//

#ifndef NLP_HASHSET_H
#define NLP_HASHSET_H


#include "myStl/Vector.h"

template <typename T>
class HashSetItem {
public:
    HashSetItem() = default;
    bool found{};
    T item;
};


template <typename T> class HashSet {
public:
    Vector<T>* set;

public:
    //Returns position to insert if not exists otherwise position
    int binarySearch(const T& key, int* positionToInsert) {
        //std::wcout << "\n-----------" << key << "----------------\n";
        int start = 0;
        int end = set->getSize() - 1;
        int mid;
        while (start <= end) {
            mid = start + (end - start) / 2;
            //std::wcout << "[ " << start << "  " << end << " ]\n";

            if(set->get(mid) == key) {
                return mid;
            }

            if(set->get(mid) < key) {
                start = mid + 1;
            } else {
                end = mid - 1;
            }
        }
        //std::wcout << "{ " << start << "  " << end << " }\n";
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
        //for(int i = 0; i < set->getSize(); ++i) {
        //    delete set->get(i);
        //}
        set->deleteAll();
    }
    ~HashSet() {
        delete set;
    }

    HashSetItem<T> get(const T& key) {
        int posToInsert = -1;
        //return binarySearch(key, posToInsert);
        HashSetItem<T> result;
        int res = binarySearch(key, &posToInsert);
        if (res == -1) {
            result.found = false;
        } else {
            result.found = true;
            result.item = set->get(res);
        }
        return result;
    }

    HashSetItem<T> put(const T& key) {
        int posToInsert = -1;
        HashSetItem<T> result;
        result.found = true;
        int res = binarySearch(key, &posToInsert);
        if (res == -1) {
            set->insertAt(posToInsert, key);
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

    T getAtPos(int i) {
        return set->get(i);
    }

    /// use very carefully
    void addInTheEndOfSetArray(T element) {
        set->add(element);
    }



};

#endif //NLP_HASHSET_H

