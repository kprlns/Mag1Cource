//
// Created by kprlns on 09.06.2020.
//

#ifndef NLP_INDEXLOADER_H
#define NLP_INDEXLOADER_H

#include <fstream>

#include "index/BucketIndex.h"
#include "index/Index.h"
#include "myStl/Pair.h"
#include "compression/VariableByte.h"

class BucketIndexLoader {
public:
    bool withVariableByte;
    Vector<unsigned char>* buffer;
    BucketIndexLoader() {}
    BucketIndexLoader(bool withVariableByte) {
        this->withVariableByte = withVariableByte;
        buffer = new Vector<unsigned char>(4096);
    }
    ~BucketIndexLoader() {
        delete buffer;
    }


    BucketIndex* load(char* filenameIndex, char* filenamePositions, char* filenameTitleForwardIndex) {
        auto start = std::chrono::steady_clock::now();
        auto flags = std::ifstream::binary | std::ifstream::in;
        BucketIndex* index = new BucketIndex();
        index->reverseIndexFilePath = filenameIndex;
        index->positionFilePath = filenamePositions;
        index->titleIndexFilePath = filenameTitleForwardIndex;

        loadIndex(filenameIndex, index, flags);
        loadPositions(filenamePositions, index, flags);
        loadTitleForwardIndex(filenameTitleForwardIndex, index, flags);
        auto end = std::chrono::steady_clock::now();
        //std::wcout << L"Load time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

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
        //std::wcout << size << std::endl;
        for(int i = 0; i < size; ++i) {
            unsigned long long hash;
            int indexSize;
            //fileIndex >> hash >> indexSize;
            fileIndex.read((char*)&hash, sizeof(unsigned long long));
            fileIndex.read((char*)&indexSize, sizeof(int));
            //std::wcout << "Size: " << indexSize << std::endl << "Hash: " << hash << std::endl;

            TermIndex* indices = new TermIndex(indexSize);
            fileIndex.read((char*)&indices->count, sizeof(indices->count));

            if(!withVariableByte) {
                indices->docIds->setSize(indexSize);
                indices->frequencies->setSize(indexSize);
                fileIndex.read((char *) indices->docIds->getData(), sizeof(int) * indexSize);
                fileIndex.read((char *) indices->frequencies->getData(), sizeof(int) * indexSize);
            } else {
                int currentSize;
                fileIndex.read((char*)&currentSize, sizeof(currentSize));
                buffer->clear();
                buffer->resize(currentSize);
                buffer->setSize(currentSize);
                fileIndex.read((char *) buffer->getData(), sizeof(unsigned char) * currentSize);
                indices->docIds = VariableByte().decode(buffer, indices->docIds);

                fileIndex.read((char*)&currentSize, sizeof(currentSize));
                buffer->clear();
                buffer->resize(currentSize);
                buffer->setSize(currentSize);
                fileIndex.read((char *) buffer->getData(), sizeof(unsigned char) * currentSize);
                indices->frequencies = VariableByte().decode(buffer, indices->frequencies);

            }
            indices->flags->setSize(indexSize);
            fileIndex.read((char *) indices->flags->getData(), sizeof(unsigned char) * indexSize);


            //for (int j = 0; j < indexSize; ++j) {
            //    fileIndex >> tmp;
            //    indices->add(tmp);
            //}
            //std::wcout << L"Insert into bucket: " << index->getBucketIndex(hash) << std::endl;
            auto element = new Pair<unsigned long long, TermIndex*>(hash, indices);
            // TODO fixed?

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
        //std::wcout << index->docPositions->getSize() << std::endl;
        //for(int i = 0; i < index->docPositions->getSize() && i < 107302; i++) {
        //    std::wcout << index->docPositions->get(i) << L" ";
        //}
        //std::wcout << std::endl;
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
            auto set = new HashMap<unsigned long long, int>(indexSize);
            //set->set->setSize(indexSize);
            for(int j = 0; j < indexSize; ++j) {
                auto* newItem = new Pair<unsigned long long, int>();
                titleForwardIndexFile.read((char*)&newItem->key, sizeof(newItem->key));
                titleForwardIndexFile.read((char*)&newItem->value, sizeof(newItem->value));
                set->set->add(newItem);
            }
            //titleForwardIndexFile.read((char*)set->set->getData(), sizeof(unsigned long long) * indexSize);
            //for(int j = 0; j < indexSize; j++) {
            //    titleForwardIndexFile >> tmp;
            //    set->addInTheEndOfSetArray(tmp);
            //}
            index->forwardIndex->add(set);
        }
        index->docSizes = new Vector<int>(size);
        index->docSizes->setSize(size);
        titleForwardIndexFile.read((char*)index->docSizes->getData(), sizeof(int) * size);
        if(!titleForwardIndexFile.is_open() || titleForwardIndexFile.fail()) {
            std::wcout << "FFFFFF1";
        }
    }

};

#endif //NLP_INDEXLOADER_H
