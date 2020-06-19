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


int main_iefnwif(int argc, char* argv[]) {
    Commons::setLocale();

    //BucketIndex *bucketIndex = Indexer().bucketIndexFile(
    //        "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json");

    Indexer().countStats(
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json");
    //bucketIndex->printAll();
/*
    BucketIndexSaver().save(
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_stem_Ind",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_stem_Pos",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_stem_Forward",
            bucketIndex
    );
*/
    //FileQueriesProcessor().loadIndexAndPerformQuery(argv[1], atoi(argv[3]) != 0, atoi(argv[2]));

}