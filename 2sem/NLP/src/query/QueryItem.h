//
// Created by kprlns on 10.06.2020.
//

#ifndef NLP_QUERYITEM_H
#define NLP_QUERYITEM_H

#include "myStl/String.h"

enum QueryItemEnum {

    OPEN_PARENTHESIS,
    CLOSE_PARENTHESIS,

    AND_OPERATOR,
    OR_OPERATOR,
    NEGATE_OPERATOR,

    OPERAND
};

class QueryItem {
public:
    QueryItemEnum itemType;
    unsigned long long operandHash;


    QueryItem(QueryItemEnum itemType) {
        this->itemType = itemType;
    }
    QueryItem(unsigned long long hash) {
        itemType = OPERAND;
        operandHash = hash;
    }

    bool isOperand() {
        return itemType == OPERAND;
    }
    bool isOperator() {
        return !isOperand();
    }

    QueryItemEnum getItemType() const {
        return itemType;
    }

    unsigned long long int getOperandHash() const {
        return operandHash;
    }

    bool isNot(QueryItemEnum other) {
        return itemType != other;
    }
    bool is(QueryItemEnum other) {
        return itemType == other;
    }

    int getPriority() {
        if(itemType == OR_OPERATOR) {
            return 1;
        }
        else if (itemType == AND_OPERATOR) {
            return 2;
        }
        else if(itemType == NEGATE_OPERATOR) {
            return 3;
        }
        else {
            return 0;
        }
    }
};

#endif //NLP_QUERYITEM_H
