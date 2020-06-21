//
// Created by kprlns on 19.06.2020.
//

#ifndef NLP_SNIPPETGENERATOR_H
#define NLP_SNIPPETGENERATOR_H

#include <dto/Document.h>
#include <index/BucketIndex.h>
#include <tokenization/Stemming.h>
#include <parser/CorpusParser.h>
#include "myStl/Vector.h"
#include "myStl/Pair.h"
#include "query/ranking/TfIdf.h"

class SnippetGeneratorResult {
public:
    double tfIdf;
    //double titleSnippetWeight;
    //double textSnippetWeight;
    bool titleSnippet;
    int snippetSentenceIndex;
    double maxSnippetWeight;
    //Vector<double>* tf;
    Vector<double>* weights;
    SnippetGeneratorResult(double tfIdf, /*double titleWeight, double textWeight,*/
            bool isSnippetInTitle, int sentence, double maxWeight, Vector<double>* weight) {
        this->tfIdf = tfIdf;
        //titleSnippetWeight = titleWeight;
        //textSnippetWeight = textWeight;
        titleSnippet = isSnippetInTitle;
        snippetSentenceIndex = sentence;
        weights = weight;
        maxSnippetWeight = maxWeight;
    }

};


class SnippetGenerator {
public:
    BucketIndex* index;
    HashMap<unsigned long long, int>* freqs;
    SnippetGenerator(BucketIndex* ind) {
        index = ind;
        freqs = new HashMap<unsigned long long, int>(100);
    }
    ~SnippetGenerator() {
        if(freqs != nullptr) {
            delete freqs;
        }
    }


    Vector<SnippetGeneratorResult*>*
            findSnippets(HashSet<unsigned long long>* operandHashes, Vector<Pair<double, int>*>* ranks, Vector<Document*>* documents, BucketIndex* index) {
        StemmedTerms stemmer;
        auto result = new Vector<SnippetGeneratorResult*>(100);
        int cnt = 0;
        for(int i = 0; i < operandHashes->getSize(); ++i) {
            //std::wcout << L"< " << operandHashes->getAtPos(i) << L" " << index->get(operandHashes->getAtPos(i)).item->value->count << L" >\n";
            freqs->put(operandHashes->getAtPos(i), index->get(operandHashes->getAtPos(i)).item->value->count);
        }

        for (int i = 0; i < ranks->getSize(); ++i) {
            result->add(findDocumentSnippet(operandHashes, stemmer, documents->get(i), ranks->get(i)->getKey()));
            cnt += 1;
        }
        freqs->set->setSize(0);
        //std::wcout << "<ol>";
        //for(int i = 0; i < 1; ++i) {
        //    printDocumentWithSnippet(documents->get(i), ranks->get(i)->getKey(),
        //            result->get(i)->weights, false);
        //}
        //std::wcout << "</ol>";
        return result;
    }

    SnippetGeneratorResult* findDocumentSnippet(HashSet<unsigned long long>* operandHashes, StemmedTerms& stemmer, Document* document, double tfIdf) {
        //String<wchar_t>* text = new String<wchar_t>(L" «Властелин колец: Братство кольца (саундтрек)» (англ. The Lord of the Rings: The Fellowship of the Ring Soundtrack) — альбом, выпущенный в 2001 году. Содержит композиции Говарда Шора, вошедшие в саундтрек первой части кинотрилогии «Властелин колец» «Властелин колец: Братство кольца»");
        //document->setText(text);
        Vector<Vector<unsigned long long>*>* titleTerms = stemmer.getSentencesStemmedTerms(document->getTitle(), true);
        Vector<Vector<unsigned long long>*>* textSentenceTerms = stemmer.getSentencesStemmedTerms(document->getText(),false);

        bool isTitle = true;
        auto* textSnippetWeights = new Vector<double>(textSentenceTerms->getSize());
        textSnippetWeights->add( evaluateWeight(titleTerms->get(0), operandHashes, 0.05, 0.04, document->getDocId()));

        double maxWeight = textSnippetWeights->get(0);
        int snippetSentenceInd = 0;
        double multiplier = 0.9;
        for(int i = 0; i < textSentenceTerms->getSize(); ++i) {
            double currentWeight = multiplier * evaluateWeight(textSentenceTerms->get(i), operandHashes, 0.04, 0.03, document->getDocId());
            textSnippetWeights->add(currentWeight);
            if(maxWeight < currentWeight) {
                maxWeight = currentWeight;
                snippetSentenceInd = i;
                isTitle = false;
            }
            multiplier *= 0.9;
        }
        return new SnippetGeneratorResult(tfIdf, isTitle, snippetSentenceInd, maxWeight, textSnippetWeights);
    }

    double evaluateWeight(Vector<unsigned long long>* sentence, HashSet<unsigned long long>* operandHashes, double baseTermValue, double increase, int docId) {
        HashMap<unsigned long long, double> tf(operandHashes->getSize());
        TfIdf tfIdf;
        for(int i = 0; i < operandHashes->getSize(); ++i) {
            tf.put(operandHashes->getAtPos(i), tfIdf.tf(docId, operandHashes->getAtPos(i), index));
        }

        bool previousIsOperand = false;
        double weight = 0;
        double currentValue = baseTermValue;
        for(int i = 0; i < sentence->getSize(); ++i) {
            unsigned long long currentTerm = sentence->get(i);
            if(operandHashes->get(currentTerm).found) {
                double tmp = freqs->get(currentTerm).getValue();
                double mult = 500 / tmp;
                weight += currentValue * mult;
                currentValue += (increase);
            } else {
                //currentValue = baseTermValue;
                currentValue = std::max(baseTermValue, currentValue - increase * 0.33);
            }
        }
        return weight;
    }

    void printDocumentWithSnippet(Document* document, double tfIdf, Vector<double>* snippetWeights, bool onlyHeaders) {
        auto start = std::chrono::steady_clock::now();
        //std::wcout << L"<ol>";
        std::wcout << L"<li><div style=\"word-wrap: break-word; max-width: 400px\"><h4>";
        //doc->print();
        std::wcout << tfIdf << L" ";
        std::wcout << L" [" << std::setprecision(3) << snippetWeights->get(0) << L" | ";
        for(int i = 1; i < snippetWeights->getSize(); ++i) {
            std::wcout  << std::setprecision(3) << snippetWeights->get(i) << " ";
        }
        std::wcout << "] ";

        document->getTitle()->print();
        std::wcout << L"</h4></div>";
        if(!onlyHeaders) {
            std::wcout << L"</br><div style=\"word-wrap: break-word; max-width: 800px\">";
            document->getText()->print();
            std::wcout << L"</div>";
        }
        std::wcout << L"</li></br></br>\n";
    }

};


#endif //NLP_SNIPPETGENERATOR_H
