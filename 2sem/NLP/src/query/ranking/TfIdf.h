//
// Created by kprlns on 17.06.2020.
//

#ifndef NLP_TFIDF_H
#define NLP_TFIDF_H

#include "index/BucketIndex.h"
#include "myStl/HashMap.h"

#include <math.h>

class TfIdf {
public:
    Vector<Pair<double, int>*>*
            ranking(Vector<int>* documents, HashSet<unsigned long long>* operandHashes, BucketIndex* index) {
        auto* rankedResult = new HashMap<double, int>(documents->getSize());
        auto* allRankedResults = new Vector<Pair<double, int>*>(documents->getSize());
        int cnt = 0;
        for(int i = 0; i < documents->getSize(); ++i) {
            double sumMult = 0;
            int currentDoc = documents->get(i);
            if(index->forwardIndex->get(currentDoc)->getSize() < 30) {
                continue;
            }
            double sumTfIdf = 0;
            for(int j = 0; j < operandHashes->getSize(); ++j) {

                unsigned long long hash = operandHashes->getAtPos(j);
                sumMult += getMultiplier(hash, currentDoc, index);
                sumTfIdf += tf(currentDoc, hash, index) * idf(hash, index) / 10;
            }
            if(abs(sumTfIdf) < 1e-9) {
                allRankedResults->add(new Pair<double, int>(sumTfIdf, currentDoc));
            } else {
                rankedResult->put(0.5 * sumMult * sumTfIdf, currentDoc);
            }
        }
        for(int i = 0; i < rankedResult->getSize(); ++i) {
            allRankedResults->add(rankedResult->getAtPos(i));
        }
        return allRankedResults;
    }

    double tf(int doc, unsigned long long operandHash, BucketIndex* index) {
        HashMap<unsigned long long, int>*
                currentForwardIndex= index->forwardIndex->get(doc);
        auto itemIndex = currentForwardIndex->get(operandHash);
        double res = 0.0;
        if(itemIndex.found) {
            res = itemIndex.getValue();
        }
        return res / sqrt(index->docSizes->get(doc));
        //return log2(res) / pow(log2(index->docSizes->get(doc)), 1);
    }

    double idf(long long operandHash, BucketIndex* index) {
        auto operandIndex = index->get(operandHash);
        if(!operandIndex.found) {
            return 0;
        }
        double totalDocs = (double)index->docSizes->getSize();
        double totalDocsWithOperand = (double)operandIndex.item->getValue()->docIds->getSize();
        return log10(totalDocs / sqrt(totalDocsWithOperand));
    }

    double getMultiplier(unsigned long long hash, int docId, BucketIndex* index) {
        unsigned char flag = getFlag(hash, docId, index);
        if(flag & TITLE) {
            return 4;
        }
        if(flag & FIRST_FIVE) {
            return 2;
        }
        return 1;
    }

    unsigned char getFlag(unsigned long long hash, int docId, BucketIndex* index) {
        auto item = index->get(hash).getValue();
        HashSet<int> binSearch(0);
        binSearch.set = item->docIds;
        auto search = binSearch.get(docId);
        binSearch.set = nullptr;
        if(!search.found) {
            return 0;
        }
        return item->flags->get(search.index);
    }

};

#endif //NLP_TFIDF_H
