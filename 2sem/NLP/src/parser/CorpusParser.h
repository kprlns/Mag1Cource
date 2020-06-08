//
// Created by Никита on 23.05.2020.
//

#ifndef NLP_CORPUSPARSER_H
#define NLP_CORPUSPARSER_H

#include <iostream>
#include <fstream>
#include <string>

#include "dto/Document.h"
#include "parser/ParserUtils.h"
#include "Common.h"

// /Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataMusic.json
class CorpusParser {
public:
    explicit CorpusParser(const char* filename) {
        input = std::wifstream(filename);
        cntLine = 0;
        init();
    }

    pos_type getPosition() {
        return input.tellg();
    }


    Document* getNextDocument() {
        auto document = new Document();
        //String<wchar_t>*
        bool isDocumentPresent = true;
        for(int i = 0; i < 3; ++i) {
            std::wstring tmpString;
            if(input.eof() || input.bad()) {
                delete document;
                return nullptr;
            }
            std::getline(input, tmpString, L'\n');
            cntLine++;
            //std::wcout << cntLine << std::endl;
            //std::wcout << tmpString << std::endl;
            String<wchar_t> line(tmpString.data(), tmpString.length());
            if(line == L"}") {
                delete document;
                return nullptr;
            }
            String<wchar_t>* key = ParserUtils::extractKey(line);
            //std::wcout << key << L'\n' << value << L"\n----\n";
            if((*key) == TITLE) {
                document->setTitle(ParserUtils::extractTextValue(line));
            }
            else if((*key) == TEXT) {
                document->setText(ParserUtils::extractTextValue(line));
            }
            else if((*key) == PAGE_ID) {
                document->setId(ParserUtils::parsePageId(line));
            }
            else {
                isDocumentPresent = false;
                break;
            }
            delete key;
        }
        if(!isDocumentPresent) {
            delete document;
            return nullptr;
        }
        skipLines(2);
        return document;
    }

    ~CorpusParser() {
        input.close();
    }
private:
    constexpr static const wchar_t TITLE[] = L"title";
    constexpr static const wchar_t PAGE_ID[] = L"pageId";
    constexpr static const wchar_t TEXT[] = L"text";

    std::wifstream input;
    int cntLine;
    void init() {
        skipLines(5);
    }
    void skipLines(int linesToSkip) {
        std::wstring str;
        for(int i = 0; i < linesToSkip; ++i) {
            std::getline(input, str);
        }
        cntLine += linesToSkip;
    }

};



#endif //NLP_CORPUSPARSER_H
