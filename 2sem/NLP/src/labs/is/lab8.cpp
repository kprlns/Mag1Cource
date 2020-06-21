//
// Created by kprlns on 17.06.2020.
//

#include <index/Indexer.h>
#include <climits>
#include <locale>
#include <clocale>
#include <query/FileQueriesProcessor.h>

#include "parser/CorpusParser.h"
#include "index/IndexSaver.h"
#include "index/IndexLoader.h"

int main(int argc, char* argv[]) {
    Commons::setLocale();
    // -O3 -march=native -mtune=native

    //String<char>(argv[1]).print() ;
    //std::wcout << std::endl << atoi(argv[2]);
    //std::wcout << std::endl << atoi(argv[3]);
    FileQueriesProcessor().loadIndexAndPerformQuery(argv[1], atoi(argv[3]) != 0, atoi(argv[2]));
    //"/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json");
// "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/queries.txt"
    return 0;

}