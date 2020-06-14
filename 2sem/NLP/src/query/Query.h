//
// Created by kprlns on 10.06.2020.
//

#ifndef NLP_QUERY_H
#define NLP_QUERY_H

#include "QueryItem.h"
#include "myStl/Vector.h"

class Query {
    Vector<QueryItem*>* query;

public:

    Query() {
        query = new Vector<QueryItem*>(32);
    }
    ~Query() {
        query->deleteAll();
        delete query;
    }

    int getSize() {
        return query->getSize();
    }
    QueryItem* get(int i) {
        return query->get(i);
    }


    Vector<QueryItem*>* getQuery() {
        return query;
    }

    void validateAndAdd(QueryItemEnum itemType) {
        if(query->getSize() > 0) {
            auto lastInserted = query->getLast();
            if((lastInserted->getItemType() == OPERAND && itemType == OPEN_PARENTHESIS)
            || (lastInserted->getItemType() == OPERAND && itemType == NEGATE_OPERATOR)
            || (lastInserted->getItemType() == CLOSE_PARENTHESIS && itemType == NEGATE_OPERATOR)) {
                //std::wcout << L"& ";
                query->add(new QueryItem(AND_OPERATOR));
            }
        }

        query->add(new QueryItem(itemType));
    }
    void validateAndAdd(unsigned long long hash) {
        if(query->getSize() > 0) {
            auto lastInserted = query->getLast();
            if(lastInserted->getItemType() == OPERAND || lastInserted->getItemType() == CLOSE_PARENTHESIS) {
                //std::wcout << L"&";
                query->add(new QueryItem(AND_OPERATOR));
            }
        }

        query->add(new QueryItem(hash));
    }



    void print() {
        for(int i = 0; i < query->getSize(); ++i) {
            QueryItem* item = query->get(i);
            if(item->isOperand()) {
                std::wcout << item->getOperandHash() << L' ';
            } else {
                if(item->getItemType() == OPEN_PARENTHESIS) {
                    std::wcout << L"( ";
                } else if(item->getItemType() == CLOSE_PARENTHESIS) {
                    std::wcout << L") ";
                } else if(item->getItemType() == AND_OPERATOR) {
                    std::wcout << L"& ";
                } else if(item->getItemType() == OR_OPERATOR) {
                    std::wcout << L"| ";
                } else if(item->getItemType() == NEGATE_OPERATOR) {
                    std::wcout<< L"! ";
                }

            }
        }
        std::wcout << std::endl;
    }

};



#endif //NLP_QUERY_H
