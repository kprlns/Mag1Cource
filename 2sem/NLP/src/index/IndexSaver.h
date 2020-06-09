//
// Created by kprlns on 09.06.2020.
//

#ifndef NLP_INDEXSAVER_H
#define NLP_INDEXSAVER_H

#include "index/Index.h"

#include <fstream>
#include <dto/BucketIndex.h>

class BucketIndexSaver {
public:

    void save(char* filenameIndex, char* filenamePositions, BucketIndex* index) {
        auto start = std::chrono::steady_clock::now();
        auto flags = std::ofstream::out | std::ofstream::trunc | std::ofstream::binary;
        std::wofstream fileIndex = std::wofstream(filenameIndex, flags);
        std::wofstream filePositions = std::wofstream(filenamePositions, flags);

        for(int i = 0; i < index->indexBuckets->getSize(); ++i) {
            saveOne(fileIndex, index->indexBuckets->get(i));
        }
        for(int i = 0; i < index->docPositions->getSize(); ++i) {
            filePositions << index->docPositions->get(i);
        }

        fileIndex.close();
        filePositions.close();
        auto end = std::chrono::steady_clock::now();
        std::wcout << L"Save time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

    }

private:

    void saveOne(std::wofstream& fileIndex, Index* index) {
        for(int i = 0; i < index->index->getSize(); ++i) {
            auto item = index->index->getAtPos(i);
            fileIndex << item->key << item->value->getSize();
            for(int j = 0; j < item->value->getSize(); ++j) {
                fileIndex << item->value->get(j);
            }
        }
    }

};

#endif //NLP_INDEXSAVER_H
