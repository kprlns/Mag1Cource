//
// Created by kprlns on 11.06.2020.
//

#ifndef NLP_QUERYPARSER_H
#define NLP_QUERYPARSER_H

#include "dto/Query.h"
#include "Common.h"

class QueryParser {
public:
    /// TODO test
    Query* parse(String<wchar_t>* string) {
        auto result = new Query();
        unsigned long long hash = INITIAL_HASH_VALUE;
        int size = 0;
        for(int i = 0; i < string->getSize(); ++i) {
            wchar_t current = string->get(i);
            if(iswalnum(current)) {
                size++;
                hash = djb2(hash, towlower(current));
            } else {
                if(size > 0) {
                    result->validateAndAdd(hash);
                    hash = INITIAL_HASH_VALUE;
                    size = 0;

                    checkOperator(result, current);
                }
            }
        }
        return result;
    }

    void checkOperator(Query* result, wchar_t current) {
        if(current == L'(') {
            result->validateAndAdd(OPEN_PARENTHESIS);
        } else if(current == L')') {
            result->validateAndAdd(CLOSE_PARENTHESIS);
        } else if(current == L'!') {
            result->validateAndAdd(NEGATE_OPERATOR);
        } else if(current == L'&') {
            result->validateAndAdd(AND_OPERATOR);
        } else if(current == L'|') {
            result->validateAndAdd(OR_OPERATOR);
        }
    }
};


#endif //NLP_QUERYPARSER_H
