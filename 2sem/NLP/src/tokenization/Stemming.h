//
// Created by kprlns on 18.06.2020.
//

#ifndef NLP_STEMMING_H
#define NLP_STEMMING_H

#include "myStl/HashSet.h"
#include "Tokenization.h"
#include "Common.h"
#include "myStl/Pair.h"

class StemmedTerms {
public:
    HashSet<unsigned long long> *reverseEndingHashes;
    const int MAX_ENDING_SIZE = 3;
    StemmedTerms() {
        reverseEndingHashes = new HashSet<unsigned long long>(128);
        putAllEndings();
    }

    Vector<unsigned long long>* getDocumentTermHashesVector(Document* document) {
        auto hashesVector = new Vector<unsigned long long>(512);
        int tmp = 0;
        countUniqueTermStatisticsVector(document->getTitle(), &tmp, hashesVector);
        countUniqueTermStatisticsVector(document->getText(), &tmp, hashesVector);
        return hashesVector;
    }

    void countUniqueTermStatisticsVector(
            String<wchar_t>* str, int* totalLength, Vector<unsigned long long>* hashes) {
        if(str == nullptr) {
            return;
        }
        int size = 0;
        int start = 0;
        int end = 0;
        unsigned long long hash = INITIAL_HASH_VALUE;
        bool setStart = false;
        int tmp;
        for(int i = 0; i < str->getSize(); ++i) {
            wchar_t currentChar = str->get(i);
            //std::wcout << "[" << currentChar << "] " << iswalnum(currentChar) << std::endl;
            if(iswalnum(currentChar)) {
                if(!setStart) {
                    setStart = true;
                    start = i;
                }
                size++;
                hash = djb2(hash, towlower(currentChar));
                //std::wcout << currentChar;
            } else {
                if (size > 0) {
                    (*totalLength) += size;
                    //hashes->add(hash);
                    hashes->add(stemTerm(str, start, i, &tmp));
                    //std::wcout << " " << hash << std::endl;
                    hash = INITIAL_HASH_VALUE;
                    size = 0;
                }
                setStart = false;
            }
        }
        if(size > 0) {
            (*totalLength) += size;
            size = 0;
            hashes->add(stemTerm(str, start, str->getSize(), &tmp));
            hash = INITIAL_HASH_VALUE;
        }
    }

    Vector<Pair<unsigned long long, int>*>* getDocumentTermHashesVectorFreq(Document* document) {
        auto hashesVector = new Vector<Pair<unsigned long long, int>*>(512);
        int tmp = 0;
        countUniqueTermStatisticsVectorWithLength(document->getTitle(), &tmp, hashesVector);
        countUniqueTermStatisticsVectorWithLength(document->getText(), &tmp, hashesVector);
        return hashesVector;
    }


    void countUniqueTermStatisticsVectorWithLength(
            String<wchar_t>* str, int* totalLength, Vector<Pair<unsigned long long, int>*>* hashes) {
        if(str == nullptr) {
            return;
        }
        int size = 0;
        int start = 0;
        int end = 0;
        unsigned long long hash = INITIAL_HASH_VALUE;
        bool setStart = false;
        int termSize;
        for(int i = 0; i < str->getSize(); ++i) {
            wchar_t currentChar = str->get(i);
            //std::wcout << "[" << currentChar << "] " << iswalnum(currentChar) << std::endl;
            if(iswalnum(currentChar)) {
                if(!setStart) {
                    setStart = true;
                    start = i;
                }
                size++;
                hash = djb2(hash, towlower(currentChar));
                //std::wcout << currentChar;
            } else {
                if (size > 0) {
                    (*totalLength) += size;
                    //hashes->add(hash);
                    hashes->add(new Pair<unsigned long long, int>(stemTerm(str, start, i, &termSize), termSize));
                    //std::wcout << " " << hash << std::endl;
                    hash = INITIAL_HASH_VALUE;
                    size = 0;
                }
                setStart = false;
            }
        }
        if(size > 0) {
            (*totalLength) += size;
            size = 0;
            hashes->add(new Pair<unsigned long long, int>(stemTerm(str, start, str->getSize(), &termSize), termSize));
            hash = INITIAL_HASH_VALUE;
        }
    }



    unsigned long long hashes[3] = {0, 0, 0};
    unsigned long long stemTerm(String<wchar_t>* string, int start, int end, int* length) {
        int termSize = end - start;
        if(termSize > 4) {
            unsigned long long endingHash = INITIAL_HASH_VALUE;
            for(int i = 0; i < 3; ++i) {
                endingHash = djb2(endingHash, string->get(end - i - 1));
                hashes[i] = endingHash;
            }
            for(int i = 2; i >= 0; --i) {
                HashSetItem<unsigned long long> item = reverseEndingHashes->get(hashes[i]);
                if(item.found) {
                    end -= (i + 1);
                    termSize -= (i + 1);
                    break;
                }
            }
        }
        //for(int i = start; i < end; ++i) {
        //    std::wcout << string->get(i);
        //}
        //std::wcout << std::endl;
        unsigned long long hash = INITIAL_HASH_VALUE;
        for(int i = start; i < end; ++i) {
            hash = djb2(hash, towlower(string->get(i)));
        }
        *length = end - start;
        return hash;
    }


    void putAllEndings() {
        int totalEndings = 84;
        for (int i = 0; i < totalEndings; ++i) {
            putOne(endings[i], sizes[i]);
        }
    }

    void putOne(const wchar_t *str, int len) {
        unsigned long long hash = INITIAL_HASH_VALUE;
        for (int i = len - 1; i >= 0; --i) {
            hash = djb2(hash, str[i]);
        }
        reverseEndingHashes->put(hash);
    }



    const wchar_t* endings[84] = {
        L"ать", L"ять", L"оть", L"еть", L"уть",
                L"у", L"ю", L"ем", L"им", L"ешь",
                L"ишь", L"ете", L"ите", L"ет", L"ит",
                L"ут", L"ют", L"ят", L"ал", L"ял",
                L"ала", L"яла", L"али", L"яли", L"ол",

                L"ел", L"ола", L"ела", L"оли", L"ели",
                L"ул", L"ула", L"ули", L"а", L"ам",
                L"ами", L"ас", L"ам", L"ая", L"е",
                L"её", L"ей", L"ем", L"еми", L"емя",
                L"ех", L"ею", L"ёт", L"ёте", L"ёх",

                L"ёшь", L"и", L"ие", L"ий", L"им",
                L"ими", L"ит", L"ите", L"их", L"ишь",
                L"ию", L"м", L"ми", L"мя", L"о",
                L"ов", L"ого", L"ое", L"оё", L"ой",
                L"ом", L"ому", L"ою", L"см", L"у",

                L"ум", L"умя", L"ут", L"ух", L"ую",
                L"шь", L"ах", L"ый", L"ые"
    };
    const int sizes[84] = {
            3, 3, 3, 3, 3,
            1, 1, 2, 2, 3,
            3, 3, 3, 2, 2,
            2, 2, 2, 2, 2,
            3, 3, 3, 3, 2,

            2, 3, 3, 3, 3,
            2, 3, 3, 1, 2,
            3, 2, 2, 2, 1,
            2, 2, 2, 3, 3,
            2, 2, 2, 3, 2,

            3, 1, 2, 2, 2,
            3, 2, 3, 2, 3,
            2, 1, 2, 2, 1,
            2, 3, 2, 2, 2,
            2, 3, 2, 2, 1,

            2, 3, 2, 2, 2,
            2, 2, 2, 2
    };
};

#endif //NLP_STEMMING_H
