//
// Created by kprlns on 18.06.2020.
//

#include <index/Indexer.h>
#include <climits>
#include <locale>

#include "parser/CorpusParser.h"
#include "index/IndexSaver.h"
#include "index/IndexLoader.h"
#include "Common.h"
#include <query/FileQueriesProcessor.h>


int main_orjn(int argc, char* argv[]) {
    Commons::setLocale();

    BucketIndex *bucketIndex = Indexer().bucketIndexFile(
            "/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json");

    //Indexer().countStats(
    //        "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json");
    //bucketIndex->printAll();

    BucketIndexSaver(true).save(
            "/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/IndCompress/cleanedDataMusic_Ind_compressed1",
            "/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/IndCompress/cleanedDataMusic_Pos_compressed1",
            "/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/IndCompress/cleanedDataMusic_Forward_compressed1",
            bucketIndex
    );

    //FileQueriesProcessor().loadIndexAndPerformQuery(argv[1], atoi(argv[3]) != 0, atoi(argv[2]));

}