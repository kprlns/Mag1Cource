//
// Created by Никита on 13.06.2020.
//

#ifndef NLP_QUERYSERVICE_H
#define NLP_QUERYSERVICE_H

#include "query/QueryParser.h"
#include "query/QueryProcessor.h"

class QueryService {
private:
    QueryParser queryParser;
    QueryProcessor queryProcessor;
    BucketIndex* bucketIndex;
public:

    QueryService(BucketIndex* bucketIndex): queryProcessor(QueryOperation()) {
        queryParser = QueryParser();
        this->bucketIndex = bucketIndex;
    }

    Vector<int>* processStringQuery(String<wchar_t>* stringQuery, HashSet<unsigned long long>* operandHashes) {
        Query* parsedQuery = queryParser.parse(stringQuery, operandHashes);
        //parsedQuery->print();
        Vector<int>* res =  queryProcessor.process(bucketIndex, parsedQuery);
        delete parsedQuery;
        return res;
    }

    Vector<int>* processStringQuery(wchar_t* string) {
        String<wchar_t> stringQuery(string);
        //TODO fix
        return processStringQuery(&stringQuery, new HashSet<unsigned long long>(32));
    }

};

#endif //NLP_QUERYSERVICE_H
