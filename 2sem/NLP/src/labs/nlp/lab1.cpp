//
// Created by kprlns on 26.05.2020.
//

#include <iostream>
#include <chrono>
#include <locale>

#include "parser/CorpusParser.h"
#include "tokenization/Tokenization.h"

struct DelimeterInteger : std::numpunct<wchar_t> {
    wchar_t do_thousands_sep() const { return L'\u200c'; }
    std::string do_grouping() const { return "~"; }
};
//set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native")

int main() {
    std::setlocale(LC_ALL,"");
    std::locale::global(std::locale("en_US.UTF-8") );
    std::ios_base::sync_with_stdio(false);
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcin.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale(std::wcin.getloc(), new DelimeterInteger));

    //std::wcout << L"Hello lab1\n";
    Vector<int> tokensCnt(4096);
    Vector<int> lengthSum(4096);
    int totalTokens = 0;
    int totalLength = 0;
    int totalDocs = 0;
    CorpusParser parser("/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json");
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