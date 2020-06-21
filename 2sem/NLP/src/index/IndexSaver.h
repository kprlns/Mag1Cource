//
// Created by kprlns on 09.06.2020.
//

#ifndef NLP_INDEXSAVER_H
#define NLP_INDEXSAVER_H

#include "index/Index.h"

#include <fstream>
#include <index/BucketIndex.h>
#include "compression/VariableByte.h"
#define writeFile(file, a) ((file).write((char*)(&(a)), sizeof(a)))

class BucketIndexSaver {
public:
    bool withVariableByte;
    Vector<unsigned char>* buffer;
    BucketIndexSaver() {};
    BucketIndexSaver(bool withVariableByte) {
        this->withVariableByte = withVariableByte;
        buffer = new Vector<unsigned char>(2048);
    }
    ~BucketIndexSaver() {
        if(buffer != nullptr) {
            delete buffer;
        }
    }

    void save(char* filenameIndex, char* filenamePositions,
            char* filenameTitleForwardIndex, BucketIndex* index) {

        auto start = std::chrono::steady_clock::now();
        auto flags = std::ofstream::out | std::ofstream::trunc | std::ofstream::binary;
        std::ofstream fileIndex = std::ofstream(filenameIndex, flags);
        std::ofstream filePositions = std::ofstream(filenamePositions, flags);
        std::ofstream fileTitleForwardIndex = std::ofstream(filenameTitleForwardIndex, flags);

        //index
        int indexSize = index->getSize();
        fileIndex.write((char*)&indexSize, sizeof(indexSize));
        for(int i = 0; i < index->numOfBuckets; ++i) {
            saveOne(fileIndex, index->indexBuckets->get(i));
        }


        //positions of documents in original file
        //filePositions << index->docPositions->getSize();
        int sizePositions = index->docPositions->getSize();
        filePositions.write((char*)&sizePositions, sizeof(sizePositions));
        filePositions.write((char*)index->docPositions->getData(),
                sizeof(index->docPositions->get(0)) * sizePositions);


        saveForwardIndex(fileTitleForwardIndex, index->forwardIndex, index->docSizes);

        fileIndex.close();
        filePositions.close();
        fileTitleForwardIndex.close();
        auto end = std::chrono::steady_clock::now();
        std::wcout << L"Save time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

    }

private:
    void saveForwardIndex(std::ofstream& fileTitleForwardIndex, Vector<HashMap<unsigned long long, int>*>* forwardIndex,
            Vector<int>* docSizes) {
        //title forward index
        int titleIndexSize = forwardIndex->getSize();
        fileTitleForwardIndex.write((char*)&titleIndexSize, sizeof(titleIndexSize));
        for(int i = 0; i < titleIndexSize; ++i) {
            auto current = forwardIndex->get(i);
            int currSize = current->getSize();
            fileTitleForwardIndex.write((char*)&currSize, sizeof(currSize));
            for(int j = 0; j < currSize; ++j) {
                Pair<unsigned long long, int>* currentItem = current->getAtPos(j);
                fileTitleForwardIndex.write((char*)&currentItem->key, sizeof(currentItem->key));
                fileTitleForwardIndex.write((char*)&currentItem->value, sizeof(currentItem->value));
            }
            //fileTitleForwardIndex.write((char*)current->set->getData(),
            //                            sizeof(current->getAtPos(0)) * currSize);
        }
        fileTitleForwardIndex.write((char*)docSizes->getData(), sizeof(docSizes->get(0)) * titleIndexSize);

    }


    void saveOne(std::ofstream& fileIndex, Index* index) {
        for(int i = 0; i < index->index->getSize(); ++i) {
            auto item = index->index->getAtPos(i);
            fileIndex.write((char*)&(item->key), sizeof(item->key));
            int itemValSize = item->value->getSize();
            fileIndex.write((char *) &itemValSize, sizeof(itemValSize));
            fileIndex.write((char *) &item->getValue()->count, sizeof(item->getValue()->count));
            if(!withVariableByte) {
                fileIndex.write((char *) item->getValue()->docIds->getData(),
                                sizeof(item->getValue()->docIds->get(0)) * itemValSize);
                fileIndex.write((char *) item->getValue()->frequencies->getData(),
                                sizeof(item->getValue()->frequencies->get(0)) * itemValSize);
            } else {
                buffer = VariableByte().encode(item->getValue()->docIds, buffer);
                int bufferSize = buffer->getSize();
                fileIndex.write((char *)&bufferSize, sizeof(bufferSize));
                fileIndex.write((char *)buffer->getData(), sizeof(unsigned char) * bufferSize);

                buffer = VariableByte().encode(item->getValue()->frequencies, buffer);
                bufferSize = buffer->getSize();
                fileIndex.write((char *)&bufferSize, sizeof(bufferSize));
                fileIndex.write((char *)buffer->getData(), sizeof(unsigned char) * bufferSize);

            }
        }
    }

};

#endif //NLP_INDEXSAVER_H
