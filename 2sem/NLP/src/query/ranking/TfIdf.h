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

        for(int i = 0; i < documents->getSize(); ++i) {
            int currentDoc = documents->get(i);
            if(index->forwardIndex->get(currentDoc)->getSize() < 10) {
                continue;
            }
            double sumTfIdf = 0;
            for(int j = 0; j < operandHashes->getSize(); ++j) {
                unsigned long long hash = operandHashes->getAtPos(j);
                sumTfIdf += tf(currentDoc, hash, index) * idf(hash, index);
            }
            if(abs(sumTfIdf) < 1e-9) {
                allRankedResults->add(new Pair<double, int>(sumTfIdf, currentDoc));
            } else {
                rankedResult->put(sumTfIdf, currentDoc);
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
        return res / index->docSizes->get(doc);
    }

    double idf(long long operandHash, BucketIndex* index) {
        auto operandIndex = index->get(operandHash);
        if(!operandIndex.found) {
            return 0;
        }
        double totalDocs = (double)index->docSizes->getSize();
        double totalDocsWithOperand = (double)operandIndex.item->getValue()->docIds->getSize();
        return log10(totalDocs / totalDocsWithOperand);
    }

};

#endif //NLP_TFIDF_H
