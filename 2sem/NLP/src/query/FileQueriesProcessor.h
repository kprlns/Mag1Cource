//
// Created by Никита on 14.06.2020.
//

#ifndef NLP_FILEQUERIESPROCESSOR_H
#define NLP_FILEQUERIESPROCESSOR_H

#include <index/BucketIndex.h>
#include <parser/CorpusParser.h>
#include "QueryService.h"

class FileQueriesProcessor {
public:
    void performAllFromFile(BucketIndex* index, char* queriesFile) {
        QueryService queryService(index);
        CorpusParser parser(index->originFilePath);
        std::wifstream queries(queriesFile);
        while(queries.is_open() && !queries.eof()) {
            std::wstring tmpString;
            std::getline(queries, tmpString, L'\n');
            if(tmpString.length() == 0) {
                continue;
            }
            String<wchar_t> line(tmpString.data(), tmpString.length());

            Vector<int>* res = queryService.processStringQuery(&line);
            QueryOperation::printVector(res);
            delete res;
        }
    }

};

#endif //NLP_FILEQUERIESPROCESSOR_H
