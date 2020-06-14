//
// Created by Никита on 12.06.2020.
//

#ifndef NLP_QUERYPROCESSOR_H
#define NLP_QUERYPROCESSOR_H

#include <index/BucketIndex.h>
#include "query/Query.h"
#include "query/QueryItem.h"
#include "QueryOperation.h"

class QueryProcessor {
public:
    QueryOperation queryOperation;
    QueryProcessor(QueryOperation queryOperation) {
        this->queryOperation = queryOperation;
    }

    Vector<int>* process(BucketIndex* index, Query* query) {
        return inversePolish(index, query);
    }
private:
    Vector<int>* inversePolish(BucketIndex* index, Query* query) {
        Vector<QueryItem*> operationsStack(32);
        Vector<Vector<int>*> operands(32);
        for(int i = 0; i < query->getSize(); i++) {
            QueryItem* current = query->get(i);
            if(current->is(OPEN_PARENTHESIS)) {
                //std::wcout << L"Query: OPEN_PARENTHESIS\n";
                operationsStack.add(current);
            } else if(current->is(CLOSE_PARENTHESIS)) {
                //std::wcout << L"Query: CLOSE_PARENTHESIS\n";
                while (operationsStack.getLast()->isNot(OPEN_PARENTHESIS)) {
                    performOne(&operationsStack, &operands, index);
                }
                operationsStack.popBack();
            } else if(current->isOperand()) {
                //std::wcout << L"Query: OPERAND\n";
                HashMapItem<unsigned long long, Vector<int>*> indexItem = index->get(current->getOperandHash());
                if(indexItem.found) {
                    operands.add(indexItem.item->value);
                } else {
                    operands.add(new Vector<int>(0));
                }
            } else if(current->isOperator()) {
                performWhilePriorityIsGreaterThenCurrent(&operationsStack, &operands, current, index);
                operationsStack.add(current);
            }
        }
        //Perform while operationsStack is not empty
        while(!operationsStack.isEmpty()) {
            performOne(&operationsStack, &operands, index);
        }
        return operands.getFirst();
    }

    void performWhilePriorityIsGreaterThenCurrent(Vector<QueryItem*>* operationsStack, Vector<Vector<int>*>* operands,
            QueryItem* current, BucketIndex* index) {
        bool isNegate = current->is(NEGATE_OPERATOR);
        while (!operationsStack->isEmpty() &&
                ((!isNegate && (operationsStack->getLast()->getPriority() >= current->getPriority())) ||
                (isNegate && (operationsStack->getLast()->getPriority() > current->getPriority()))))
        {
            //Perform operation
            performOne(operationsStack, operands, index);
        }
    }

    bool performOne(Vector<QueryItem*>* operationsStack, Vector<Vector<int>*>* operands, BucketIndex* index) {
        QueryItem* operation = operationsStack->getLast();
        bool performed = false;
        if(operation->is(NEGATE_OPERATOR)) {
            performNegation(operands, index->getTotalDocumentsNumber());
            performed = true;
        } else if(operation->is(OR_OPERATOR) || operation->is(AND_OPERATOR)) {
            performBinaryOperation(operands, operation);
            performed = true;
        } else if(operation->is(OPEN_PARENTHESIS)) {
            std::wcout << "ALARM ALARM: OPEN_PARENTHESIS" << std::endl;
        }
        if(performed) {
            operationsStack->popBack();
        }
        return performed;
    }

    void performNegation(Vector<Vector<int>*>* operands, int totalDocsNum) {
        Vector<int>* last = operands->getLast();
        Vector<int>* negated = queryOperation.negate(last, totalDocsNum);
        delete last;
        operands->popBack();
        operands->add(negated);
    }

    void performBinaryOperation(Vector<Vector<int>*>* operands, QueryItem* operation) {
        Vector<int>* first = operands->get(operands->getSize() - 1);
        Vector<int>* second = operands->get(operands->getSize() - 2);
        Vector<int>* operationResult = queryOperation.binaryOperation(first, second, operation);
        operands->popBack();
        operands->popBack();
        operands->add(operationResult);
    }
};
#endif //NLP_QUERYPROCESSOR_H