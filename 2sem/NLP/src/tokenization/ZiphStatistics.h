//
// Created by kprlns on 18.06.2020.
//

#ifndef NLP_ZIPHSTATISTICS_H
#define NLP_ZIPHSTATISTICS_H

#include <index/BucketIndex.h>
#include <index/IndexLoader.h>
#include <myStl/BucketHashSet.h>

class FrequencyPair {
public:
    unsigned long long hash;
    int frequency;
    FrequencyPair() = default;
    FrequencyPair(unsigned long long hash, int frequency) {
        this->hash = hash;
        this->frequency = frequency;
    }

    int operator<(const FrequencyPair& other) {
        return (frequency > other.frequency) || ((frequency == other.frequency) && (hash > other.hash));
    }
    int operator>(const FrequencyPair& other) {
        return (frequency < other.frequency) || ((frequency == other.frequency) && (hash < other.hash));
    }
    int operator==(const FrequencyPair& other) {
        return (hash == other.hash) && (frequency == other.frequency);
    }
};

class ZiphStatistics {
public:
    void calc() {
        BucketIndex *bucketIndex = BucketIndexLoader().load(
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Ind",
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Pos",
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Forward"
        );
        bucketIndex->originFilePath = "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic.json";

        HashSet<FrequencyPair> freqs(2000000);
        for (int i = 0; i < bucketIndex->indexBuckets->getSize(); ++i) {
            HashMap<unsigned long long, TermIndex *> *
                    currentBucket = bucketIndex->indexBuckets->get(i)->index;
            for (int j = 0; j < currentBucket->getSize(); ++j) {
                auto currentItem = currentBucket->getAtPos(j);
                freqs.put(FrequencyPair(currentItem->key, currentItem->value->count));
            }
            if (i % 10000 == 0) {
                std::wcout << i << L" / " << bucketIndex->indexBuckets->getSize() << std::endl;
            }
        }

        for (int i = 0; i < freqs.getSize(); ++i) {
            std::wcout << freqs.getAtPos(i).frequency << ",";
        }
        //for(int i = 1000; i < freqs.getSize(); i += 1000) {
        //    std::wcout << freqs.getAtPos(i).frequency << ",";
        //}
        //std::wcout << std::endl;
        //for()
    }

};


#endif //NLP_ZIPHSTATISTICS_H
/*
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Ind",
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Pos",
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/cleanedDataMusic_Forward"



                                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Ind",
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Pos",
                "/home/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut1_Forward"

 */