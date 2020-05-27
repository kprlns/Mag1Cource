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
    static Vector< String<wchar_t >* >* makeTokens(Document* document) {
        auto* result = new Vector< String<wchar_t>* >(256);
        addAllSplits(document->getTitle(), result);
        addAllSplits(document->getText(), result);
        return result;
    }


private:

    static void addAllSplits(String<wchar_t>* toAdd, Vector< String<wchar_t>* >* result) {
        auto* tokens = toAdd->split(L' ');
        int tokensSize = tokens->getSize();
        for(int i = 0; i < tokensSize; ++i) {
            //std::wcout << i << L"(" << (*tokens->get(i)) << L")" << std::endl;
            addAllSubtokens(tokens->get(i), L'-', result);
            result->add(tokens->get(i));
        }
        delete tokens;
    }

    static inline void addAllSubtokens(String<wchar_t>* string, wchar_t splitter, Vector< String<wchar_t>* >* result) {
        auto* splittedToken = string->splitIfContains(splitter);
        if(splittedToken != nullptr) {
            int splittedSize = splittedToken->getSize();
            for(int j = 0; j < splittedSize && splittedSize > 1; j++) {
                result->add(splittedToken->get(j));
            }
            delete splittedToken;
        }
    }
};

#endif //NLP_TOKENIZATION_H
