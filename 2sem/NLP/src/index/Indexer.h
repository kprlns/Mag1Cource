//
// Created by Никита on 07.06.2020.
//

#ifndef NLP_INDEXER_H
#define NLP_INDEXER_H

#include <chrono>

#include "tokenization/Tokenization.h"
#include "dto/Index.h"
#include "parser/CorpusParser.h"

class Indexer {
public:

    Index* indexFile(char* filename) {
        Index* index = new Index();
        CorpusParser parser(filename);
        auto start = std::chrono::steady_clock::now();
        int cnt = 0;
        while (true) {
            cnt++;
            Document *document = parser.getNextDocument();
            if(document == nullptr) {
                break;
            }
            //79,129,329
            //40,331,459
            //Tokenization::countUniqueTermStatistics(document, &totalLength, &totalTokens, &totalDocs);
            auto hashes = Tokenization::getDocumentTermHashes(document);
            index->putAll(hashes, cnt, parser.getPosition());

            if(true) {
                std::wcout << cnt << std::endl;
                //break;
            }
        }
        auto end = std::chrono::steady_clock::now();

        //std::wcout << L"Total length: " << totalLength << L"\n";
        //std::wcout << L"Total tokens: " << totalTokens << L"\n";
        //std::wcout << L"Total docs: " << totalDocs << L"\n";
        //std::wcout.imbue(std::locale())
        std::wcout << L"Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
        return index;
    }
};


#endif //NLP_INDEXER_H
