//
// Created by kprlns on 17.06.2020.
//

#ifndef NLP_TERMS_H
#define NLP_TERMS_H

#include "Tokenization.h"
#include "myStl/Vector.h"
#include "myStl/BucketHashMap.h"
#include "myStl/HashSet.h"
#include "dto/Document.h"

class Terms {
public:
    void getAllTerms(Document *document, BucketHashMap<unsigned long long, int>* hashes) {
        putAllTerms(document->getTitle(), hashes);
        putAllTerms(document->getText(), hashes);
    }

    void putAllTerms(String<wchar_t>* str, BucketHashMap<unsigned long long, int>* hashes) {
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
                //std::wcout << currentChar;
            } else if(size > 0 ) {
                if(size < Tokenization::MAX_TOKEN_SIZE) {
                    hashes->put(hash, size);
                }
                //std::wcout << " " << hash << std::endl;
                hash = INITIAL_HASH_VALUE;
                size = 0;
            }
        }
        if(size > 0) {
            hashes->put(hash, size);
            //std::wcout << " " << hash << std::endl;
            hash = INITIAL_HASH_VALUE;
            size = 0;

        }
    }

    void countStatistics(BucketHashMap<unsigned long long, int>* hashes) {
        int totalTermsCount = hashes->getSize();
        int totalTermsSize = 0;
        for(int i = 0; i < hashes->bucketMap->getSize(); ++i) {
            HashMap<unsigned long long, int>* currentMap = hashes->bucketMap->get(i);
            for(int j = 0; j < currentMap->getSize(); ++j) {
                totalTermsSize += currentMap->getAtPos(j)->value;
            }
        }
        std::wcout << L"Total terms: " << totalTermsCount << std::endl;
        std::wcout << L"Total terms length: " << totalTermsSize << std::endl;
    }

};

#endif //NLP_TERMS_H
