//
// Created by kprlns on 10.06.2020.
//

#include <index/Indexer.h>
#include <climits>

#include "parser/CorpusParser.h"
#include "index/IndexLoader.h"

int main_is() {
    std::setlocale(LC_ALL, "");
    std::locale::global(std::locale("en_US.UTF-8"));
    std::ios_base::sync_with_stdio(false);
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcin.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale(std::wcin.getloc(), new DelimeterInteger));

    BucketIndex *bucketIndex = Indexer().bucketIndexFile(
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1.json");
    bucketIndex->printAll();
    //bucketIndex->printPositions();
    BucketIndex* index = BucketIndexLoader().load(
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/indexTest",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/positionsTest",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/titleTest"
            );
    std::wcout << L"\n===---===---===---===---===---===---===---===---===---===---===---===---===\n";
    index->printAll();
    //index->printIndex();
    //index->printPositions();
    delete index;
    delete bucketIndex;

    return 0;
}
/*
        auto f = std::ifstream("/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/indexTest", std::ios::binary);
    if ( (f.rdstate() & std::ifstream::failbit ) != 0 )
        std::wcout << "Error opening file\n";
    while(!f.eof() && f.is_open() && !f.bad()) {
        int a = 0;
        f.read((char*)&a, sizeof(int));
        std::wcout << a  << std::endl;
        break;
    }
    return 0;

 */