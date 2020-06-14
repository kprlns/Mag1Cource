//
// Created by Никита on 13.06.2020.
//

#ifndef NLP_QUERYOPERATION_H
#define NLP_QUERYOPERATION_H

#include "myStl/Vector.h"
#include "QueryItem.h"

#include <algorithm>

class QueryOperation {
private:

public:
    static void printVector(Vector<int>* vector) {
        for(int i = 0; i < vector->getSize(); ++i) {
            std::wcout << vector->get(i) << L" ";
        }
        std::wcout << std::endl;
    }

    Vector<int>* binaryOperation(Vector<int>* first, Vector<int>* second, QueryItem* operation) {
        if(operation->is(OR_OPERATOR)) {
            return unite(first, second);
        }
        if(operation->is(AND_OPERATOR)) {
            return intersect(first, second);
        }
        return nullptr;
    }

    Vector<int>* intersect(Vector<int>* first, Vector<int>* second) {
        //std::wcout << L"Intersect: \n";
        //printVector(first);
        //printVector(second);
        int iFirst = 0;
        int iSecond = 0;
        auto result = new Vector<int>(std::min(first->getSize(), second->getSize()));
        while(iFirst < first->getSize() && iSecond < second->getSize()) {
            int firstItem = first->get(iFirst);
            int secondItem = second->get(iSecond);
            if(firstItem == secondItem) {
                result->add(firstItem);
                iFirst++;
                iSecond++;
            } else if(firstItem > secondItem) {
                iSecond++;
            } else {
                iFirst++;
            }
        }
        //std::wcout << "Result: \n";
        //printVector(result);
        return result;
    }

    Vector<int>* unite(Vector<int>* first, Vector<int>* second) {
        //std::wcout << L"Unite: \n";
        //printVector(first);
        //printVector(second);
        int iFirst = 0;
        int iSecond = 0;
        int firstSize = first->getSize();
        int secondSize = second->getSize();
        auto result = new Vector<int>(std::max(first->getSize(), second->getSize()));
        while(iFirst < firstSize || iSecond < secondSize) {
            int firstItem, secondItem;
            if(iFirst < firstSize) {
                firstItem = first->get(iFirst);
            }
            if(iSecond < secondSize) {
                secondItem = second->get(iSecond);
            }

            if(iFirst >= first->getSize()) {
                result->add(secondItem);
                iSecond++;
                continue;
            } else if(iSecond >= second->getSize()) {
                result->add(firstItem);
                iFirst++;
                continue;
            }
            if(firstItem == secondItem) {
                result->add(firstItem);
                iFirst++;
                iSecond++;
            } else if((firstItem > secondItem)) {
                result->add(secondItem);
                iSecond++;
            } else if((firstItem < secondItem)) {
                result->add(firstItem);
                iFirst++;
            }
        }
        if(iSecond)
        //std::wcout << "Result: \n";
        //printVector(result);
        return result;
    }

    Vector<int>* negate(Vector<int>* first, int totalDocuments) {
        //std::wcout << L"Negate: " << totalDocuments << L"\n";
        //printVector(first);
        int iFirst = 0;
        int firstItem = first->get(iFirst);
        auto result = new Vector<int>(totalDocuments - first->getSize());
        for(int i = 0; i < totalDocuments; ++i) {
            if(iFirst >= first->getSize()) {
                result->add(i);
                continue;
            }

            if(i < firstItem) {
                result->add(i);
            } else if(i > firstItem) {
                if(iFirst < first->getSize() - 1) {
                    iFirst++;
                    firstItem = first->get(iFirst);
                    i--;
                    continue;
                } else {
                    result->add(i);
                }
            } else { // i == firstItem
                if(iFirst < first->getSize() - 1) {
                    iFirst++;
                    firstItem = first->get(iFirst);
                }
            }
        }
        //std::wcout << "Result: \n";
        //printVector(result);
        return result;
    }
};




#endif //NLP_QUERYOPERATION_H
