//
// Created by kprlns on 26.05.2020.
//

#include <iostream>
#include <chrono>
#include <locale>

#include "parser/CorpusParser.h"
#include "Common.h"
#include "tokenization/Tokenization.h"

#include <wctype.h>
#include <clocale>



void calcTokenizationStatistics(const char* filename) {
    int totalLength = 0;
    int totalTokens = 0;
    int totalDocs = 0;
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
        Tokenization::countUniqueTermStatistics(document, &totalLength, &totalTokens, &totalDocs);
        if(cnt % 100000 == 0) {
            //std::wcout << cnt << std::endl;
            //break;
        }
    }
    auto end = std::chrono::steady_clock::now();

    std::wcout << L"Total length: " << totalLength << L"\n";
    std::wcout << L"Total tokens: " << totalTokens << L"\n";
    std::wcout << L"Total docs: " << totalDocs << L"\n";
    //std::wcout.imbue(std::locale())
    std::wcout << L"Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

}

void calcHonestTokenizationStatistics(const char* filename) {
    Vector<int> tokensCnt(4096);
    Vector<int> lengthSum(4096);
    int totalTokens = 0;
    int totalLength = 0;
    int totalDocs = 0;
    CorpusParser parser(filename);
    auto start = std::chrono::steady_clock::now();
    while (true) {
        Document *document = parser.getNextDocument();
        if(document == nullptr) {
            break;
        }
        auto *splits = Tokenization::makeTokens(document);
        totalDocs++;
        totalTokens += splits->getSize();
        for (int i = 0; i < splits->getSize(); ++i) {
            totalLength += splits->get(i)->getSize();
            //std::wcout << L"|" << (*splits->get(i)) << L"|\n";
        }
        //std::wcout << L"=============================\n";
        splits->deleteAll();
        delete splits;
        delete document;
    }
    auto end = std::chrono::steady_clock::now();

    std::wcout << L"Total length: " << totalLength << L"\n";
    std::wcout << L"Total tokens: " << totalTokens << L"\n";
    std::wcout << L"Total docs: " << totalDocs << L"\n";
    //std::wcout.imbue(std::locale())
    std::wcout << L"Elapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

}

int main_nlp_lab1() {

    std::setlocale(LC_ALL,"");
    std::locale::global(std::locale("en_US.UTF-8") );
    std::ios_base::sync_with_stdio(false);
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcin.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale(std::wcin.getloc(), new DelimeterInteger));

    //"/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json"
    calcTokenizationStatistics("/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json");
    return 0;
}

/*
     int a = 1;
    int* b = &a;
    (*b)++;
    std::wcout << a << "!\n";

    String<wchar_t>* testStr = new String(L"a~b.– \"n' c-d,e.f?g![]АБВГДабвгд↑/\n");
    for(int i = 0; i < testStr->getSize(); ++i) {
        std::wcout << (*testStr)[i] << L" " << (unsigned long long) (*testStr)[i] << ": " << std::boolalpha
                   << (iswalnum((*testStr)[i]) != 0) << std::endl;
    }
    return 0;
 */