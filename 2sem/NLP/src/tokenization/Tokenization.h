//
// Created by kprlns on 26.05.2020.
//

#ifndef NLP_TOKENIZATION_H
#define NLP_TOKENIZATION_H

#include "myStl/Vector.h"
#include "myStl/String.h"
#include "myStl/HashSet.h"
#include "dto/Document.h"

class Tokenization {
public:
    static Vector< String<wchar_t >* >* makeTokens(Document* document) {
        auto* result = new Vector< String<wchar_t>* >(256);
        addAllSplits(document->getTitle(), result);
        addAllSplits(document->getText(), result);
        return result;
    }

    static void countTokensStatistics(Document* document, int* totalLength, int* totalTokens, int* totalDocs) {
        (*totalDocs)++;
        countTokenStatistics(document->getTitle(), totalLength, totalTokens);
        countTokenStatistics(document->getText(), totalLength, totalTokens);
    }

    static void countUniqueTermStatistics(Document* document, int* totalLength, int* totalTokens, int* totalDocs) {
        (*totalDocs)++;

        auto hashes = new HashSet<unsigned long long>(512);
        countUniqueTermStatistics(document->getTitle(), totalLength, hashes);
        countUniqueTermStatistics(document->getText(), totalLength, hashes);

        (*totalTokens) += hashes->getSize();
        delete hashes;
    }

    static HashSet<unsigned long long>* getDocumentTermHashes(Document* document) {
        auto hashes = new HashSet<unsigned long long>(512);
        int tmp = 0;
        countUniqueTermStatistics(document->getTitle(), &tmp, hashes);
        countUniqueTermStatistics(document->getText(), &tmp, hashes);

        return hashes;
    }


private:
    static const unsigned long long INITIAL_HASH_VALUE = 5381;

    static void countUniqueTermStatistics(
            String<wchar_t>* str, int* totalLength, HashSet<unsigned long long>* hashes) {
        if(str == nullptr) {
            return;
        }
        int size = 0;
        unsigned long long hash = INITIAL_HASH_VALUE;
        for(int i = 0; i < str->getSize(); ++i) {
            wchar_t currentChar = str->get(i);
            if(iswalnum(currentChar)) {
                size++;
                hash = djb2(hash, towlower(currentChar));
                std::wcout << currentChar;
            } else if(size > 0) {
                (*totalLength) += size;
                size = 0;
                hashes->put(hash);
                std::wcout << " " << hash << std::endl;
                hash = INITIAL_HASH_VALUE;
            }
        }
        if(size > 0) {
            (*totalLength) += size;
            size = 0;
            hashes->put(hash);
            std::wcout << " " << hash << std::endl;
            hash = INITIAL_HASH_VALUE;
        }
    }

    static inline unsigned long long djb2(unsigned long long currentHash, wchar_t c) {
        return (currentHash << 13) + (currentHash << 5) + currentHash + c;
    }



    static void countTokenStatistics(String<wchar_t>* str, int* totalLength, int* totalTokens) {
        int size = 0;
        for(int i = 0; i < str->getSize(); ++i) {
            if(iswalnum(str->get(i))) {
                size++;
            } else if(size > 0) {
                (*totalLength) += size;
                (*totalTokens) += 1;
                size = 0;
            }
        }
    }

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
