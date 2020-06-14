//
// Created by Никита on 07.06.2020.
//

#ifndef NLP_INDEXER_H
#define NLP_INDEXER_H

#include <chrono>

#include "tokenization/Tokenization.h"
#include "Index.h"
#include "BucketIndex.h"
#include "parser/CorpusParser.h"
#include <vector>
#include <algorithm>

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
            index->putAll(hashes, cnt - 1, document->getPosition());
            delete hashes;
            if(cnt % 1000 == 0) {
                std::wcout << cnt << std::endl;
                //break;
            }

        }
        auto end = std::chrono::steady_clock::now();

        //std::wcout << L"Total length: " << totalLength << L"\n";
        std::wcout << L"Total tokens: " << index->index->getSize() << L"\n";
        //std::wcout << L"Total docs: " << totalDocs << L"\n";
        //std::wcout.imbue(std::locale())
        std::wcout << L"Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
        return index;
    }

    BucketIndex* bucketIndexFile(char* filename) {
        BucketIndex* index = new BucketIndex();
        index->originFilePath = filename;
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
            index->putAll(hashes, cnt - 1, document->getPosition());
            delete hashes;
            index->putTitleForwardIndex(Tokenization::getStringTermHashes(document->getTitle()));
            if(cnt % 1000 == 0) {
                std::wcout << cnt << std::endl;
                //break;
            }

        }
        auto end = std::chrono::steady_clock::now();

        //std::wcout << L"Total length: " << totalLength << L"\n";
        //std::wcout << L"Total tokens: " << index->getSize() << L"\n";
        //std::wcout << L"Total docs: " << totalDocs << L"\n";
        //std::wcout.imbue(std::locale())
        //std::wcout << L"Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
        std::vector<int> sz;
        for(int i = 0; i < index->indexBuckets->getSize(); ++i) {
            sz.push_back(index->indexBuckets->get(i)->index->getSize());
        }
        //std::sort(sz.begin(), sz.end());
        //std::wcout << L"Min bucket size: " << sz[0] << std::endl;
        //std::wcout << L"Max bucket size: " << sz[sz.size() - 1] << std::endl;
        //std::wcout << L"1/4 bucket size: " << sz[sz.size() / 4] << std::endl;
        //std::wcout << L"3/4 bucket size: " << sz[sz.size() * 3 / 4] << std::endl;
        //std::wcout << L"Avg bucket size: " << sz[sz.size() / 2] << std::endl;


        return index;
    }
};


#endif //NLP_INDEXER_H
