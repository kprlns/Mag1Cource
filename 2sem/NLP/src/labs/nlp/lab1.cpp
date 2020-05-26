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

    CorpusParser parser("/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGames.json");
    Document* document = parser.getNextDocument();
    auto* splits = Tokenization::split(document);
    for(int i = 0; i < splits->getSize(); ++i) {
        std::wcout << L"|" << (*splits->get(i)) << L"|\n";
    }
    splits->deleteAll();
    delete splits;
    delete document;
}