//
// Created by Никита on 20.06.2020.
//

#ifndef NLP_HTMLGENERATOR_H
#define NLP_HTMLGENERATOR_H

#include <iostream>

#include "dto/Document.h"
#include "query/snippets/SnippetGenerator.h"
#include "query/ranking/TfIdf.h"

class HtmlGenerator {
public:
    BucketIndex* index;
    HashSet<unsigned long long>* operandHashes;

    HtmlGenerator(BucketIndex* ind, HashSet<unsigned long long>* operands) {
        index = ind;
        operandHashes = operands;
    }


    void generateOutputWithSnippetsForOneDoc(Document* document, double tfIdf, Vector<double>* snippetWeights, bool onlyHeaders) {
        auto start = std::chrono::steady_clock::now();
        //std::wcout << L"<ol>";
        std::wcout << L"<li><div style=\"word-wrap: break-word; max-width: 400px\"><h3>";
        //doc->print();
        std::wcout << tfIdf << L" ";
        std::wcout << L" [" << snippetWeights->get(0) << L" | ";
        for(int i = 1; i < snippetWeights->getSize(); ++i) {
            std::wcout << snippetWeights->get(i) << " ";
        }
        std::wcout << "] ";

        document->getTitle()->print();
        std::wcout << L"</h3></div>";
        if(!onlyHeaders) {
            std::wcout << L"</br><div style=\"word-wrap: break-word; max-width: 800px\">";
            document->getText()->print();
            std::wcout << L"</div>";
        }
        std::wcout << L"</li></br></br>\n";
    }

    void printAllDocumentsWithSnippets(Vector<Document*>* documents, Vector<SnippetGeneratorResult*>* snippets, bool onlyHeaders, int maxRes) {
        HashMap<double, Pair<Document*, SnippetGeneratorResult*>> sortedBySnippets(100);
        for(int i = 0; i < snippets->getSize(); ++i) {
            sortedBySnippets.put( snippets->get(i)->tfIdf + snippets->get(i)->sum,
                    Pair<Document*, SnippetGeneratorResult*>(documents->get(i), snippets->get(i)));
        }

        int cnt = 0;
        std::wcout << "<ol>";
        //for(int i = 0; i < documents->getSize() && cnt < maxRes; ++i) {
        for(int i = sortedBySnippets.getSize() - 1; i >= 0 && cnt < maxRes; --i) {
            cnt++;
            auto current = sortedBySnippets.getAtPos(i);
            printDocumentWithSnippet(current->getValue().getKey(), current->getValue().getValue(), onlyHeaders);
            //printDocumentWithSnippet(documents->get(i), snippets->get(i), onlyHeaders);
        }
        std::wcout << "</ol>";
    }

    void printDocumentWithSnippet(Document* document, SnippetGeneratorResult* snippet, bool onlyHeaders) {
        //double tfIdf, Vector<double>* snippetWeights,
        double tfIdf = snippet->tfIdf;
        Vector<double>* snippetWeights = snippet->weights;

        auto start = std::chrono::steady_clock::now();
        //std::wcout << L"<ol>";
        std::wcout << L"<li><div style=\"word-wrap: break-word; max-width: 400px\"><h4>";
        //doc->print();
        std::wcout << L"[";
        std::wcout << tfIdf << L" | ";
        std::wcout << std::setprecision(3) << snippet->maxSnippetWeight << L"] "; //<< document->getDocId() << " ";
        //for(int i = 0; i < operandHashes->getSize(); ++i) {
        //    std::wcout << "{ " << TfIdf().tf(document->getDocId(), operandHashes->getAtPos(i), index) << L" "
        //               << operandHashes->getAtPos(i) << " }";
        //}

        //for(int i = 1; i < snippetWeights->getSize(); ++i) {
        //    std::wcout  << std::setprecision(3) << snippetWeights->get(i) << " ";
        //}
        //std::wcout << "] ";
        if(snippet->titleSnippet) {
            std::wcout << L"<i>";
            document->getTitle()->print();
            std::wcout << L"</i>";
        } else {
            document->getTitle()->print();
        }
        std::wcout << L"</h4></div>";
        if(!onlyHeaders) {
            int sentenceCnt = 0;
            std::wcout << L"</br><div style=\"word-wrap: break-word; max-width: 800px\">";
            //document->getText()->print();
            if(!snippet->titleSnippet && snippet->snippetSentenceIndex == 0) {
                std::wcout << L"<i><h3>";
            }
            for(int i = 0; i < document->getText()->getSize(); ++i) {
                wchar_t current = document->getText()->get(i);
                if (Commons::isSentenceSplitter(current)) {
                    std::wcout << current;
                    sentenceCnt++;
                    if(!snippet->titleSnippet && sentenceCnt == snippet->snippetSentenceIndex) {
                        std::wcout << L"<i><h3>";
                    } else if(!snippet->titleSnippet && sentenceCnt == (snippet->snippetSentenceIndex + 1)) {
                        std::wcout << L"</i></h3>";
                    }
                } else {
                    std::wcout << current;
                }
            }

            std::wcout << L"</div>";
        }
        std::wcout << L"</li></br></br>\n";
    }


};


#endif //NLP_HTMLGENERATOR_H
