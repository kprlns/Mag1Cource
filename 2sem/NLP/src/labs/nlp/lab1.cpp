//
// Created by kprlns on 26.05.2020.
//

#include <iostream>
#include "parser/CorpusParser.h"
#include "tokenization/Tokenization.h"

int main() {
    std::setlocale(LC_ALL,"");
    std::locale::global(std::locale("en_US.UTF-8") );
    std::ios_base::sync_with_stdio(false);
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcin.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale("en_US.UTF-8"));

    //std::wcout << L"Hello lab1\n";
    Vector<int> tokensCnt(4096);
    Vector<int> lengthSum(4096);
    int totalTokens = 0;
    int totalLength = 0;
    int totalDocs = 0;
    CorpusParser parser("/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json");
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
    std::wcout << L"Total length: " << totalLength << L"\n";
    std::wcout << L"Total tokens: " << totalTokens << L"\n";
    std::wcout << L"Total docs: " << totalDocs << L"\n";

}