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
#include <bitset>
#include <dto/TermIndex.h>


class Index {
public:
    HashMap<unsigned long long, TermIndex*>* index;
    Vector<pos_type>* docPositions;

    Index() {
        index = new HashMap<unsigned long long, TermIndex*>(2048);
        docPositions = new Vector<pos_type>(1);
    }
    Index(unsigned long long size) {
        index = new HashMap<unsigned long long, TermIndex*>(size);
        docPositions = new Vector<pos_type>(1);
    }
    ~Index() {
        for (int i = 0; i < index->set->getSize(); ++i) {
            delete index->set->get(i)->value;
        }
        delete docPositions;
        delete index;
    }

    void putAll(HashSet<unsigned long long>* allHashes, int docId, pos_type docPosition) {
        for(int i = 0; i < allHashes->getSize(); ++i) {
            putOne(allHashes->getAtPos(i), docId);
        }
        //docPositions->add(docPosition);
    }

    HashMapItem<unsigned long long, TermIndex*> putOne(unsigned long long hash, int docId) {
        //auto newPair = new Pair<unsigned long long, Vector<int>*>(hash, nullptr);
        auto setItem = index->put(hash, nullptr);
        if(setItem.item->value == nullptr) {
            setItem.item->value = new TermIndex(64);
        }
        if((setItem.item->value->getSize() == 0) || (docId != setItem.item->value->docIds->getLast())) {
            setItem.item->value->add(docId,1);
        } else {
            setItem.item->value->increaseFreqLast(1);
        }
        return setItem;
    }

    HashMapItem<unsigned long long, TermIndex*> get(unsigned long long hash) {
        return index->get(hash);
    }

    void printIndex() {
        for(int i = 0; i < index->getSize(); ++i) {
            auto pair = index->getAtPos(i);
            std::wcout << std::bitset<64>(pair->key) << " ";
            std::wcout << pair->key << " : ";
            for(int j = 0; j < pair->value->getSize(); ++j) {
                std::wcout << pair->value->docIds->get(j) << " ";
            }
            std::wcout << std::endl;
        }
    }
    void printIndexWithFreq() {
        for(int i = 0; i < index->getSize(); ++i) {
            auto pair = index->getAtPos(i);
            std::wcout << std::bitset<64>(pair->key) << " ";
            std::wcout << pair->key << " : ";
            for(int j = 0; j < pair->value->getSize(); ++j) {
                std::wcout << L"( " << pair->value->docIds->get(j) << L", " << pair->value->frequencies->get(j) << L") ";
            }
            std::wcout << L" [ " << pair->value->count << " ] ";
            std::wcout << std::endl;
        }
    }

    void printPositions() {
        std::wcout << "\n----------------------\n";
        for(int i = 0; i < docPositions->getSize(); ++i) {
            std::wcout << docPositions->get(i) << " ";
        }
        std::wcout << std::endl;
    }


};

#endif //NLP_INDEX_H
