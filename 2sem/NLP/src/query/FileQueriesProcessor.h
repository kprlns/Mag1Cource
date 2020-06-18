//
// Created by Никита on 14.06.2020.
//

#ifndef NLP_FILEQUERIESPROCESSOR_H
#define NLP_FILEQUERIESPROCESSOR_H

#include <index/BucketIndex.h>
#include <parser/CorpusParser.h>
#include <index/IndexLoader.h>
#include "QueryService.h"
#include "query/ranking/TfIdf.h"
#include "iomanip"

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
            //TODO fix
            Vector<int>* res = queryService.processStringQuery(&line, new HashSet<unsigned long long>(1));
            QueryOperation::printVector(res);
            delete res;
        }
    }

    void loadIndexAndPerformQuery(char* queriesFile, bool onlyHeaders, int numRes) {
        BucketIndex* bucketIndex = BucketIndexLoader().load(
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_stem_Ind",
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_stem_Pos",
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_stem_Forward"
/*                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Ind",
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Pos",
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Forward"*/
        );
        bucketIndex->originFilePath = "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json";

        auto start = std::chrono::steady_clock::now();
        performAllFromFileAndPrintAsHtml(bucketIndex, queriesFile, onlyHeaders, numRes);
        auto end = std::chrono::steady_clock::now();
        std::wcout << L"\n<p>Суммарное время: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << L"</p>";
        std::wcout << L"\n<p>Всё время указано в микросекундах</p>";

    }

    void performAllFromFileAndPrintAsHtml(BucketIndex* index, char* queriesFile, bool onlyHeaders, int numRes) {
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
            HashSet<unsigned long long>* operandHashes = new HashSet<unsigned long long>(32);

            auto start = std::chrono::steady_clock::now();
            Vector<int>* res = queryService.processStringQuery(&line, operandHashes);
            auto end = std::chrono::steady_clock::now();
            auto startRank = std::chrono::steady_clock::now();
            Vector<Pair<double, int>*>* rankedRes = TfIdf().ranking(res, operandHashes, index);
            auto endRank = std::chrono::steady_clock::now();


            //long pageFormTime = resolveResultAndPrint(res, index, onlyHeaders, numRes);
            long pageFormTime = resolveResultAndPrintRankedResult(rankedRes, index, onlyHeaders, numRes);

            std::wcout << L"\n<p>Найдено результатов: " << res->getSize() << L"</p>";
            std::wcout << L"\n<p>Время поиска по индексу: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << L"</p>";
            std::wcout << L"\n<p>Время ранжирования: " << std::chrono::duration_cast<std::chrono::microseconds>(endRank - startRank).count() << L"</p>";
            std::wcout << L"\n<p>Время поиска формирования выдачи: " << pageFormTime << L"</p>";
            //QueryOperation::printVector(res);
            delete res;
        }
    }
    long resolveResultAndPrintRankedResult(Vector<Pair<double, int>*>* res, BucketIndex* index, bool onlyHeaders, int numRes) {
        CorpusParser parser(index->originFilePath);
        auto start = std::chrono::steady_clock::now();
        std::wcout << L"<ol>";
        int cnt = 0;
        for(int i = res->getSize() - 1; i >= 0 && cnt < numRes; --i) {
            cnt++;
            parser.setPosition(index->getPosition(res->get(i)->getValue()));
            Document* doc = parser.getNextDocument();
            std::wcout << L"<li><div style=\"word-wrap: break-word; max-width: 400px\"><h2>";
            std::wcout << L"[" << std::fixed << std::setprecision(4) << res->get(i)->getKey() << "] ";
            //doc->print();
            doc->getTitle()->print();
            std::wcout << L"</h2></div>";
            if(!onlyHeaders) {
                std::wcout << L"</br><div style=\"word-wrap: break-word; max-width: 800px\">";
                doc->getText()->print();
                std::wcout << L"</div>";
            }
            std::wcout << L"</li></br></br>\n";
            delete doc;
        }
        std::wcout << L"</ol>";
        auto end = std::chrono::steady_clock::now();
        //std::wcout << L"<p>IndexSearchTime: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << L"</p></br>";
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }

    long resolveResultAndPrint(Vector<int>* res, BucketIndex* index, bool onlyHeaders, int numRes) {
        CorpusParser parser(index->originFilePath);
        auto start = std::chrono::steady_clock::now();
        std::wcout << L"<ol>";
        for(int i = 0; i < res->getSize() && i < numRes; ++i) {
            parser.setPosition(index->getPosition(res->get(i)));
            Document* doc = parser.getNextDocument();
            std::wcout << L"<li><div style=\"word-wrap: break-word; max-width: 400px\"><h2>";
            //doc->print();
            doc->getTitle()->print();
            std::wcout << L"</h2></div>";
            if(!onlyHeaders) {
                std::wcout << L"</br><div style=\"word-wrap: break-word; max-width: 800px\">";
                doc->getText()->print();
                std::wcout << L"</div>";
            }
            std::wcout << L"</li></br></br>\n";
            delete doc;
        }
        std::wcout << L"</ol>";
        auto end = std::chrono::steady_clock::now();
        //std::wcout << L"<p>IndexSearchTime: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << L"</p></br>";
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }


};

#endif //NLP_FILEQUERIESPROCESSOR_H
