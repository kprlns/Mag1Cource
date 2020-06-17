//
// Created by Никита on 06.06.2020.
//

#include <index/Indexer.h>
#include <climits>
#include <locale>
#include <clocale>

#include "parser/CorpusParser.h"
#include "index/IndexSaver.h"
#include "index/IndexLoader.h"

int main() {
    auto start = std::chrono::steady_clock::now();

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
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1.json");
    bucketIndex->printIndex();
    bucketIndex->printPositions();
/*    BucketIndexSaver().save(
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Ind",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Pos",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Title",
            bucketIndex
    );*/
    //bucketIndex->printAll();
    //BucketIndex* loaded = BucketIndexLoader().load(
    //        "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Ind",
    //        "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Pos",
    //        "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Title"
    //        );
    //std::wcout << L"\n\n-=-=-=-=-=-=-=-=-=-=-=--=-=-=-\n\n" << std::endl;

    //loaded->printAll();

    delete bucketIndex;
    auto end = std::chrono::steady_clock::now();
    std::wcout << L"Total elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << std::endl;
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
