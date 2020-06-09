//
// Created by Никита on 06.06.2020.
//

#include <index/Indexer.h>
#include <climits>

#include "parser/CorpusParser.h"
#include "index/IndexSaver.h"

int main() {

    std::setlocale(LC_ALL, "");
    std::locale::global(std::locale("en_US.UTF-8"));
    std::ios_base::sync_with_stdio(false);
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcin.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale(std::wcin.getloc(), new DelimeterInteger));

    //CorpusParser parser("/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1.json");
    //parser.testSetPosition(48);
    //parser.getNextDocument()->print();
    //parser.testSetPosition(269);
    //parser.getNextDocument()->print();
    //return 0;

    BucketIndex *bucketIndex = Indexer().bucketIndexFile(
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json");
    //bucketIndex->printIndex();
    //bucketIndex->printPositions();
    BucketIndexSaver().save(
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/index1",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/positions1",
            bucketIndex
    );
    delete bucketIndex;
    return 0;
}

//unsigned long long a = ULLONG_MAX;
//std::wcout << a << std::endl;
//std::wcout << (a >> (64 - 8));
//std::wcout << (1 << 8) << std::endl;
//return 0;
// "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json"
//Index* index = Indexer().indexFile("/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1.json");
//index->printIndex();
//delete index;
//std::wcout << "\n==============================\n";
