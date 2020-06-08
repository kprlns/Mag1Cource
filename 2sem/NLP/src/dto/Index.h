//
// Created by Никита on 07.06.2020.
//

#ifndef NLP_INDEX_H
#define NLP_INDEX_H

#include "myStl/HashSet.h"
#include "myStl/HashMap.h"
#include "myStl/Pair.h"
#include "myStl/Vector.h"
#include "Common.h"


class Index {
public:
    HashMap<unsigned long long, Vector<int>*>* index;
    Vector<pos_type>* docPositions;


    Index() {
        index = new HashMap<unsigned long long, Vector<int>*>(100000);
        docPositions = new Vector<pos_type>(108000);
    }
    ~Index() {
        delete docPositions;
        index->deleteAll();
        delete index;
    }

    void putAll(HashSet<unsigned long long>* allHashes, int docId, pos_type docPosition) {
        for(int i = 0; i < allHashes->getSize(); ++i) {
            putOne(allHashes->getAtPos(i), docId);
        }
        docPositions->add(docPosition);
    }

    void putOne(unsigned long long hash, int docId) {
        //auto newPair = new Pair<unsigned long long, Vector<int>*>(hash, nullptr);
        auto setItem = index->put(hash, nullptr);
        if(setItem.item->value == nullptr) {
            setItem.item->value = new Vector<int>(512);
        }
        setItem.item->value->add(docId);
    }

    void printIndex() {
        for(int i = 0; i < index->getSize(); ++i) {
            auto pair = index->getAtPos(i);
            std::wcout << pair->key << " : ";
            for(int j = 0; j < pair->value->getSize(); ++j) {
                std::wcout << pair->value->get(j) << " ";
            }
            std::wcout << std::endl;
        }
        std::wcout << "\n----------------------\n";
        for(int i = 0; i < docPositions->getSize(); ++i) {
            std::wcout << docPositions->get(i) << " ";
        }
        std::wcout << std::endl;
    }


};

#endif //NLP_INDEX_H
