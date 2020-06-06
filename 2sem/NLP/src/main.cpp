//
// Created by Никита on 02.05.2020.
//

#include <vector>
#include <locale>
#include <iostream>
#include <string>
#include <parser/CorpusParser.h>
#include <clocale>

#include "myStl/String.h"

int main1() {
    //auto a = std::vector<int>(2, 0);
    //std::cout << a[9999] << "\n";
    //a[9999] = 3;
    //std::cout << a.at(9999) << "\n" << a.size() << '\n' << a.max_size();

    std::wstring aaa(L"abcde");
    auto str = new String(aaa.data(), aaa.length());
    std::wcout << L"(" << ((*str) == L"abcde") << L")\n";
    //str->print();


    std::setlocale(LC_ALL,"");
    std::locale::global(std::locale("en_US.UTF-8") );
    std::ios_base::sync_with_stdio(false);
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcin.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale("en_US.UTF-8"));

    CorpusParser parser("/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGames.json");
    //Document* doc = parser.getNextDocument();
    //std::wcout << doc->getText()->operator[](0) << L"\n" << doc->getText()->operator[](doc->getText()->getSize() - 1) << L'\n';

    int i = 0;
    while(true) {
        Document* doc = parser.getNextDocument();
        if(doc == nullptr) {
            break;
        }
        i++;
        std::wcout << L"-------------\n" << i << std::endl;
        delete doc;
    }
    std::wcout << L"-------------\n" << i << std::endl;
    //delete doc;
    return 0;
}