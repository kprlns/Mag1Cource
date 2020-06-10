//
// Created by kprlns on 09.06.2020.
//

#ifndef NLP_INDEXLOADER_H
#define NLP_INDEXLOADER_H

#include <fstream>

#include "index/BucketIndex.h"
#include "index/Index.h"
#include "myStl/Pair.h"

class BucketIndexLoader {
public:
    BucketIndexLoader() {}

    BucketIndex* load(char* filenameIndex, char* filenamePositions, char* filenameTitleForwardIndex) {
        auto flags = std::ifstream::binary | std::ifstream::in;
        BucketIndex* index = new BucketIndex();

        loadIndex(filenameIndex, index, flags);
        loadPositions(filenamePositions, index, flags);
        loadTitleForwardIndex(filenameTitleForwardIndex, index, flags);

        return index;
    }

    void loadIndex(char* filenameIndex, BucketIndex* index, std::ios::openmode flags) {
        std::ifstream fileIndex = std::ifstream(filenameIndex, flags);
        if(!fileIndex.is_open() || fileIndex.fail()) {
            std::wcout << "FFFFFF1";
        }
        int size;
        fileIndex.read((char*)&size, sizeof(int));
        if(!fileIndex.is_open() || fileIndex.fail()) {
            std::wcout << "FFFFFF2";
        }
        std::wcout << size << std::endl;
        for(int i = 0; i < size; ++i) {
            unsigned long long hash;
            int indexSize;
            //fileIndex >> hash >> indexSize;
            fileIndex.read((char*)&hash, sizeof(unsigned long long));
            fileIndex.read((char*)&indexSize, sizeof(int));
            std::wcout << "Size: " << indexSize << std::endl << "Hash: " << hash << std::endl;

            auto *indices = new Vector<int>(indexSize);
            indices->setSize(indexSize);
            fileIndex.read((char*)indices->getData(), sizeof(int) * indexSize);
            //for (int j = 0; j < indexSize; ++j) {
            //    fileIndex >> tmp;
            //    indices->add(tmp);
            //}
            std::wcout << L"Insert into bucket: " << index->getBucketIndex(hash) << std::endl;
            auto element = new Pair<unsigned long long, Vector<int> *>(hash, indices);
            index->indexBuckets->get(index->getBucketIndex(hash))->index->set->add(element);
        }
    }


    void loadPositions(char* filenamePositions, BucketIndex* index, std::ios::openmode flags) {
        std::ifstream filePositions = std::ifstream(filenamePositions, flags);
        int positionsSize;
        //filePositions >> positionsSize;
        filePositions.read((char*)&positionsSize, sizeof(positionsSize));
        index->docPositions->setSize(positionsSize);
        filePositions.read((char*)index->docPositions->getData(), sizeof(pos_type) * positionsSize);
        //for(int i = 0; i < positionsSize; ++i) {
        //    filePositions >> position;
        //    index->docPositions->add(pos_type(position));
        //}
    }

    void loadTitleForwardIndex(char* filenameTitleForwardIndex, BucketIndex* index, std::ios::openmode flags) {

        std::ifstream titleForwardIndexFile = std::ifstream(filenameTitleForwardIndex, flags);
        int size;
        //titleForwardIndexFile >> size;
        titleForwardIndexFile.read((char*)&size, sizeof(size));

        for(int i = 0; i < size; ++i) {
            int indexSize;
            //titleForwardIndexFile >> indexSize;
            titleForwardIndexFile.read((char*)&indexSize, sizeof(indexSize));
            auto set = new HashSet<unsigned long long>(indexSize);
            set->set->setSize(indexSize);
            titleForwardIndexFile.read((char*)set->set->getData(), sizeof(unsigned long long) * indexSize);
            //for(int j = 0; j < indexSize; j++) {
            //    titleForwardIndexFile >> tmp;
            //    set->addInTheEndOfSetArray(tmp);
            //}
            index->titleForwardIndex->add(set);
        }
    }

};

#endif //NLP_INDEXLOADER_H
