//
// Created by Никита on 02.05.2020.
//

#include <vector>
#include <locale>
#include <iostream>
#include <string>
#include <parser/CorpusParser.h>

#include "myStl/String/String.h"

int main() {
    //auto a = std::vector<int>(2, 0);
    //std::cout << a[9999] << "\n";
    //a[9999] = 3;
    //std::cout << a.at(9999) << "\n" << a.size() << '\n' << a.max_size();

    std::wstring aaa(L"abcde");
    auto str = new String(aaa.data(), aaa.length());
    std::wcout << L"(" << ((*str) == L"abcde") << L")\n";
    //str->print();

    CorpusParser parser("/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGames.json");
    Document* doc = parser.getDocument();
    delete doc;
    return 0;
}