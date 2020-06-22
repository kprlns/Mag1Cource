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
#include "myStl/BucketHashMap.h"
#include "tokenization/Stemming.h"

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

    BucketIndex* bucketIndexWithZones(char* filename) {
        StemmedTerms stemmer;
        BucketIndex* index = new BucketIndex();
        index->originFilePath = filename;
        CorpusParser parser(filename);
        int totalLength = 0;
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
            //auto hashes = Tokenization::getDocumentTermHashesVector(document);

            auto stemmerBuffer = stemmer.getDocumentTermHashesVectorWithZones(document, 5);

            //index->putAllVector(hashes, cnt - 1, document->getPosition());
            index->putAllFromStemmerBuffer(stemmerBuffer, cnt - 1, document->getPosition());
            //index->putTitleForwardIndex(hashes);
            index->putTitleForwardIndexFromBuffer(stemmerBuffer);

            //delete hashes;
            if(cnt % 1000 == 0) {
                std::wcout << cnt << std::endl;
                //break;
            }
            delete document;

        }
        auto end = std::chrono::steady_clock::now();

        std::wcout << L"Total length: " << totalLength << L"\n";
        std::wcout << L"Total tokens: " << index->getSize() << L"\n";
        //std::wcout << L"Total docs: " << totalDocs << L"\n";
        std::wcout << L"Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
        std::vector<int> sz;
        for(int i = 0; i < index->indexBuckets->getSize(); ++i) {
            sz.push_back(index->indexBuckets->get(i)->index->getSize());
        }
        std::sort(sz.begin(), sz.end());
        std::wcout << L"Min bucket size: " << sz[0] << std::endl;
        std::wcout << L"Max bucket size: " << sz[sz.size() - 1] << std::endl;
        std::wcout << L"1/4 bucket size: " << sz[sz.size() / 4] << std::endl;
        std::wcout << L"3/4 bucket size: " << sz[sz.size() * 3 / 4] << std::endl;
        std::wcout << L"Avg bucket size: " << sz[sz.size() / 2] << std::endl;
        return index;
    }


    BucketIndex* bucketIndexFile(char* filename) {
        StemmedTerms stemmer;
        BucketIndex* index = new BucketIndex();
        index->originFilePath = filename;
        CorpusParser parser(filename);
        int totalLength = 0;
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
            //auto hashes = Tokenization::getDocumentTermHashesVector(document);
            auto hashes = stemmer.getDocumentTermHashesVector(document);
            index->putAllVector(hashes, cnt - 1, document->getPosition());
            index->putTitleForwardIndex(hashes);
            delete hashes;
            if(cnt % 1000 == 0 || cnt > 107200) {
                std::wcout << cnt << std::endl;
                //break;
            }
            delete document;

        }
        auto end = std::chrono::steady_clock::now();

        std::wcout << L"Total length: " << totalLength << L"\n";
        std::wcout << L"Total tokens: " << index->getSize() << L"\n";
        //std::wcout << L"Total docs: " << totalDocs << L"\n";
        std::wcout << L"Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
        std::vector<int> sz;
        for(int i = 0; i < index->indexBuckets->getSize(); ++i) {
            sz.push_back(index->indexBuckets->get(i)->index->getSize());
        }
        std::sort(sz.begin(), sz.end());
        std::wcout << L"Min bucket size: " << sz[0] << std::endl;
        std::wcout << L"Max bucket size: " << sz[sz.size() - 1] << std::endl;
        std::wcout << L"1/4 bucket size: " << sz[sz.size() / 4] << std::endl;
        std::wcout << L"3/4 bucket size: " << sz[sz.size() * 3 / 4] << std::endl;
        std::wcout << L"Avg bucket size: " << sz[sz.size() / 2] << std::endl;
        return index;
    }


    void countStats(char* filename) {
        StemmedTerms stemmer;
        auto* index = new BucketHashMap<unsigned long long, int>();
        CorpusParser parser(filename);
        int totalLength = 0;
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
            //auto hashes = Tokenization::getDocumentTermHashesVector(document);
            auto hashes = stemmer.getDocumentTermHashesVectorFreq(document);
            for(int i = 0; i < hashes->getSize(); ++i) {
                auto cur = hashes->get(i);
                index->put(cur->key, cur->value);
            }

            delete hashes;
            if(cnt % 1000 == 0) {
                std::wcout << cnt << std::endl;
                //break;
            }
            delete document;

        }
        for(int i = 0; i < index->bucketMap->getSize(); ++i) {
            auto curMap = index->bucketMap->get(i);
            for(int j = 0; j < curMap->getSize(); ++j) {
                totalLength += curMap->getAtPos(j)->value;
            }
        }
        auto end = std::chrono::steady_clock::now();

        std::wcout << L"Total length: " << totalLength << L"\n";
        std::wcout << L"Total tokens: " << index->getSize() << L"\n";
        //std::wcout << L"Total docs: " << totalDocs << L"\n";
        std::wcout << L"Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    }
};


#endif //NLP_INDEXER_H
