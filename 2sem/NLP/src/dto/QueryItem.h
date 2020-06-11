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
    QueryItemEnum itemType;
    unsigned long long operandHash;

public:
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

};

#endif //NLP_QUERYITEM_H
