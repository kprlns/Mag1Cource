//
// Created by kprlns on 10.06.2020.
//

#ifndef NLP_QUERY_H
#define NLP_QUERY_H

#include "dto/QueryItem.h"
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

    void validateAndAdd(QueryItemEnum itemType) {
        auto lastInserted = query->getLast();
        if(lastInserted->getItemType() == OPERAND || lastInserted->getItemType() == OPEN_PARENTHESIS) {
            query->add(new QueryItem(AND_OPERATOR));
        }

        query->add(new QueryItem(itemType));
    }
    void validateAndAdd(unsigned long long hash) {
        auto lastInserted = query->getLast();
        if(lastInserted->getItemType() == OPERAND || lastInserted->getItemType() == CLOSE_PARENTHESIS) {
            query->add(new QueryItem(AND_OPERATOR));
        }

        query->add(new QueryItem(hash));
    }

};



#endif //NLP_QUERY_H
