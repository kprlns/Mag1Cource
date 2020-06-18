//
// Created by kprlns on 11.06.2020.
//

#ifndef NLP_QUERYPARSER_H
#define NLP_QUERYPARSER_H

#include "query/Query.h"
#include "Common.h"
#include "tokenization/Stemming.h"

class QueryParser {
public:
    Query* parse(String<wchar_t>* string, HashSet<unsigned long long>* operandHashes) {
        StemmedTerms stemmer;
        auto result = new Query();
        unsigned long long hash = INITIAL_HASH_VALUE;
        int size = 0;
        bool isOp = false;
        bool setStart = false;
        int start = 0;
        int tmp;
        for(int i = 0; i < string->getSize(); ++i) {
            wchar_t current = string->get(i);
            if(iswalnum(current)) {
                if(!setStart) {
                    setStart = true;
                    start = i;
                }
                //std::wcout << (wchar_t)tolower(current);
                size++;
                //hash = djb2(hash, towlower(current));
            } else {
                if(size > 0) {
                    //std::wcout << L" ";
                    hash = stemmer.stemTerm(string, start, i, &tmp);
                    result->validateAndAdd(hash);
                    operandHashes->put(hash);
                    hash = INITIAL_HASH_VALUE;
                    size = 0;
                    isOp = isOp || checkOperator(result, current);
                } else {
                    isOp = isOp || checkOperator(result, current);
                }
                setStart = false;
            }
        }
        if(size > 0) {
            //std::wcout << " ";
            hash = stemmer.stemTerm(string, start, string->getSize(), &tmp);
            operandHashes->put(hash);
            result->validateAndAdd(hash);
        }

        //result->print();
        //std::wcout << std::endl;
        return result;
    }

    bool checkOperator(Query* result, wchar_t current) {
        if(current == L'(') {
            result->validateAndAdd(OPEN_PARENTHESIS);
            return true;
            //std::wcout << current << L' ';
        } else if(current == L')') {
            result->validateAndAdd(CLOSE_PARENTHESIS);
            return true;
            //std::wcout << current << L' ';
        } else if(current == L'!') {
            result->validateAndAdd(NEGATE_OPERATOR);
            return true;
            //std::wcout << current << L' ';
        } else if(current == L'&') {
            result->validateAndAdd(AND_OPERATOR);
            return true;
            //std::wcout << current << L' ';
        } else if(current == L'|') {
            return true;
            result->validateAndAdd(OR_OPERATOR);
            //std::wcout << current << L' ';
        }
        return false;
    }


};

/*
        if(!isOp) {
            //for(int i = 0; i < result->getSize(); ++i) {
            //    if(result->get(i)->isOperator()) {
            //        result->get(i)->itemType = OR_OPERATOR;
            //    }
            //}
            int cntOperand = 0;
            int cntOr = 0;
            QueryItem* prevOperand;
            auto resultTmp = new Query();
            //result->print();
            for(int i = 0; i < result->getSize(); ++i) {
                if(result->get(i)->isOperand()) {
                    if(cntOperand == 0) {
                        prevOperand = result->get(i);
                    } else {
                        if(cntOr > 0) {
                            resultTmp->validateAndAdd(OR_OPERATOR);
                        }
                        resultTmp->validateAndAdd(OPEN_PARENTHESIS);
                        resultTmp->validateAndAdd(prevOperand->operandHash);
                        resultTmp->validateAndAdd(AND_OPERATOR);
                        resultTmp->validateAndAdd(result->get(i)->operandHash);
                        resultTmp->validateAndAdd(CLOSE_PARENTHESIS);
                        cntOr++;
                        prevOperand = result->get(i);
                    }
                    cntOperand++;
                }
                //resultTmp->print();
            }
            delete result;
            result = resultTmp;











                    if(!isOp) {
            //for(int i = 0; i < result->getSize(); ++i) {
            //    if(result->get(i)->isOperator()) {
            //        result->get(i)->itemType = OR_OPERATOR;
            //    }
            //}
            int cntOperand = 0;
            int cntOr = 0;
            auto resultTmp = new Query();
            //result->print();

            if(operandHashes->getSize() == 1) {
                resultTmp->validateAndAdd(operandHashes->getAtPos(0));
            } else {
                int cntHashes = operandHashes->getSize();
                for(int i = 1; i < cntHashes; ++i) {
                    for(int j = 0; j < i; ++j) {
                        resultTmp->validateAndAdd(OPEN_PARENTHESIS);
                        resultTmp->validateAndAdd(operandHashes->getAtPos(i));
                        resultTmp->validateAndAdd(AND_OPERATOR);
                        resultTmp->validateAndAdd(operandHashes->getAtPos(j));
                        resultTmp->validateAndAdd(CLOSE_PARENTHESIS);
                        if((i == cntHashes - 1) && (j == cntHashes - 2)) {
                            continue;
                        }
                        resultTmp->validateAndAdd(OR_OPERATOR);
                    }
                }
            }
            delete result;
            result = resultTmp;

        }
}
 */


#endif //NLP_QUERYPARSER_H
