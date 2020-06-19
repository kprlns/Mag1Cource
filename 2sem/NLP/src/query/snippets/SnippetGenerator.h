//
// Created by kprlns on 19.06.2020.
//

#ifndef NLP_SNIPPETGENERATOR_H
#define NLP_SNIPPETGENERATOR_H

#include <dto/Document.h>
#include <index/BucketIndex.h>
#include <tokenization/Stemming.h>
#include "myStl/Vector.h"
#include "myStl/Pair.h"

class SnippetGeneratorResult {
public:
    double tfIdf;
    double titleSnippetWeight;
    double textSnippetWeight;
    bool titleSnippet;
    int snippetSentenceIndex;

    SnippetGeneratorResult(double tfIdf, double titleWeight, double textWeight, bool isSnippetInTitle, int sentence) {
        this->tfIdf = tfIdf;
        titleSnippetWeight = titleWeight;
        textSnippetWeight = textWeight;
        titleSnippet = isSnippetInTitle;
        snippetSentenceIndex = sentence;
    }

};


class SnippetGenerator {
public:
    Vector<SnippetGeneratorResult*>*
            findSnippets(HashSet<unsigned long long>* operandHashes, Vector<Pair<double, int>*>* ranks, Vector<Document*>* documents, BucketIndex* index) {
        StemmedTerms stemmer;
        for (int i = 0; i < documents->getSize() && i < 100; ++i) {

        }

        return nullptr;
    }

    void findDocumentSnippet(HashSet<unsigned long long>* operandHashes, StemmedTerms& stemmer, Document* document) {
        Vector<Vector<unsigned long long>*>* titleTerms = stemmer.getSentencesStemmedTerms(document->getTitle(), true);
        Vector<Vector<unsigned long long>*>* textSentenceTerms = stemmer.getSentencesStemmedTerms(document->getTitle(), true);

    }

    double evaluateWeight(Vector<unsigned long long>* sentence, HashSet<unsigned long long>* operandHashes, double baseTermValue, double increase) {
        bool previousIsOperand = false;
        double weight = 0;
        double currentValue = baseTermValue;
        for(int i = 0; i < sentence->getSize(); ++i) {
            unsigned long long currentTerm = sentence->get(i);
            if(operandHashes->get(currentTerm).found) {
                weight += currentValue;
                currentValue += increase;
            } else {
                currentValue = baseTermValue;
            }
        }
        return weight;
    }




};


#endif //NLP_SNIPPETGENERATOR_H
