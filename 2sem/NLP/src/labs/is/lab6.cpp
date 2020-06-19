//
// Created by kprlns on 19.06.2020.
//

#include <index/BucketIndex.h>
#include <index/Indexer.h>
#include <index/IndexLoader.h>
#include <index/IndexSaver.h>
#include "Common.h"

int main() {
    Commons::setLocale();
    //std::wcout << L"!!" << sizeof(char);
    //std::wcout << L"!!!" << (0b10000000);

    //BucketIndex *bucketIndex = Indexer().bucketIndexFile(
    //        "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json");

    auto startFull = std::chrono::steady_clock::now();
    BucketIndex *bucketIndex1 = BucketIndexLoader(false).load(
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Ind",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Pos",
            "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic"
    );
    auto endFull = std::chrono::steady_clock::now();


    auto startCompr = std::chrono::steady_clock::now();
    //BucketIndex *bucketIndex2 = BucketIndexLoader(true).load(
    //        "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Ind_compressed",
    //        "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Pos_compressed",
    //        "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Forward_compressed"
    //);
    auto endCompr = std::chrono::steady_clock::now();

    //bucketIndex->printAll();
    std::wcout << L"Elapsed time full: " << std::chrono::duration_cast<std::chrono::milliseconds>(endFull - startFull).count() << std::endl;

    std::wcout << L"\n\n-=-=-=-=--=-=-=-=-=-=-=-=\n\n";
    std::wcout << L"Elapsed time compr: " << std::chrono::duration_cast<std::chrono::milliseconds>(endCompr - startCompr).count() << std::endl;

    //bucketIndex1->printAll();
    //std::wcout << L"!!Equals: " << bucketIndex->equals(bucketIndex1);
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