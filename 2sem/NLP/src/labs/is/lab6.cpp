//
// Created by kprlns on 19.06.2020.
//

#include <index/BucketIndex.h>
#include <index/Indexer.h>
#include <index/IndexLoader.h>
#include <index/IndexSaver.h>
#include "Common.h"

int main_ejwnfkejk() {
    Commons::setLocale();
    //std::wcout << L"!!" << sizeof(char);
    //std::wcout << L"!!!" << (0b10000000);

    //BucketIndex *bucketIndex = Indexer().bucketIndexFile(
    //        "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json");
    auto startLoad = std::chrono::steady_clock::now();
    BucketIndex* bucketIndex1 = Indexer().bucketIndexWithZones(
            "/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json"
    );

    BucketIndexSaver(true).save(
            "/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/IndCompress/cleanedDataMusic_Ind_compressed2_not_stem",
            "/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/IndCompress/cleanedDataMusic_Pos_compressed2_not_stem",
            "/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/IndCompress/cleanedDataMusic_Forward_compressed2_not_stem",
            bucketIndex1
    );

    BucketIndex *bucketIndex2 = BucketIndexLoader(true).load(
            "/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/IndCompress/cleanedDataMusic_Ind_compressed2_not_stem",
            "/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/IndCompress/cleanedDataMusic_Pos_compressed2_not_stem",
            "/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/IndCompress/cleanedDataMusic_Forward_compressed2_not_stem"
            );

    //bucketIndex1->printAll();

    auto endLoad = std::chrono::steady_clock::now();
    std::wcout << L"Elapsed time full: "
               << std::chrono::duration_cast<std::chrono::milliseconds>(endLoad - startLoad).count() << std::endl;

    std::wcout << "Equals: " << bucketIndex1->equals(bucketIndex2);
}

/*
     BucketIndex *bucketIndex = Indexer().bucketIndexFile(
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1.json");

    BucketIndexSaver(true).save(
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Ind",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Pos",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Forward",
            bucketIndex
    );


    BucketIndex *bucketIndex1 = BucketIndexLoader(true).load(
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Ind",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Pos",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Forward"
    );
 */