//
// Created by kprlns on 26.05.2020.
//

#ifndef NLP_TOKENIZATION_H
#define NLP_TOKENIZATION_H

#include "myStl/Vector/Vector.h"
#include "myStl/String/String.h"
#include "dto/Document.h"

class Tokenization {
public:
    static Vector< String<wchar_t >* >* split(Document* document) {
        auto* result = new Vector< String<wchar_t>* >(256);
        addAllSplits(document->getTitle(), result);
        addAllSplits(document->getText(), result);
        return result;
    }


private:

    static void addAllSplits(String<wchar_t>* toAdd, Vector< String<wchar_t>* >* result) {
        auto* tokens = toAdd->split(L' ');
        for(int i = 0; i < tokens->getSize(); ++i) {
            std::wcout << i << L"(" << (*tokens->get(i)) << L")" << std::endl;
            auto* splittedToken = tokens->get(i)->splitIfContains(L'-');
            if(splittedToken != nullptr) {
                for(int j = 0; j < splittedToken->getSize(); j++) {
                    result->add(splittedToken->get(j));
                }
                delete splittedToken;
            }
            result->add(tokens->get(i));
        }
        delete tokens;
    }
};

#endif //NLP_TOKENIZATION_H
