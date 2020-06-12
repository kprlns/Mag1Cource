//
// Created by Никита on 12.06.2020.
//

#ifndef NLP_QUERYPROCESSOR_H
#define NLP_QUERYPROCESSOR_H

#include <index/BucketIndex.h>
#include "query/Query.h"
#include "query/QueryItem.h"

class QueryProcessor {
    Vector<int>* process(BucketIndex* index, Query* query) {

    }

    Vector<int>* inversePolish(BucketIndex* index, Query* query) {
        Vector<QueryItem*> operationsStack(32);
        Vector<Vector<int>*> operands(32);
        auto result = new Vector<int>(128);
        for(int i = 0; i < query->getSize(); i++) {
            QueryItem* current = query->get(i);
            if(current->is(OPEN_PARENTHESIS)) {
                operationsStack.add(current);
            } else if(current->is(CLOSE_PARENTHESIS)) {
                // perform
                performWhilePriorityIsGreaterThenCurrent(&operationsStack, &operands, current);
                operationsStack.add(current);
            } else if(current->isOperator()) {
                operands.add(index->get(current->getOperandHash()).item->value);
            }
        }
        //Perform while operationsStack is not empty
    }

    void performWhilePriorityIsGreaterThenCurrent(Vector<QueryItem*>* operationsStack, Vector<Vector<int>*>* operands, QueryItem* current) {
        while (!operationsStack->isEmpty() &&
                ((current->isNot(NEGATE_OPERATOR) && (operationsStack->getLast()->getPriority() >= current->getPriority())) ||
                (current->is(NEGATE_OPERATOR) && (operationsStack->getLast()->getPriority() > current->getPriority()))))
        {
            //Perform operation
        }
    }
};

#endif //NLP_QUERYPROCESSOR_H
