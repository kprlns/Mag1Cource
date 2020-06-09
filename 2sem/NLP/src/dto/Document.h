//
// Created by Никита on 22.05.2020.
//

#ifndef NLP_DOCUMENT_H
#define NLP_DOCUMENT_H

#include "Common.h"
#include <myStl/String.h>

class Document {
public:
    Document() {
        text = nullptr;
        title = nullptr;
    }
    Document(String<wchar_t>* title, String<wchar_t>* text, long long id, pos_type posType) {
        this->title = title;
        this->text = text;
        this->id = id;
        this->position = posType;
    }

    ~Document() {
        delete text;
        delete title;
    }

    [[nodiscard]] long long int getId() const { return id; }
    [[nodiscard]] String<wchar_t>* getTitle() const { return title; }
    [[nodiscard]] String<wchar_t>* getText() const { return text; }
    [[nodiscard]] pos_type getPosition() const { return position; }

    void setId(long long int id) { this->id = id; }
    void setTitle(String<wchar_t>* title) { this->title = title; }
    void setText(String<wchar_t>* text) { this->text = text; }
    void setPosition(pos_type position) { this->position = position; }

    void print() {
        std::wcout << "Title: [";
        title->print();
        std::wcout << "]\n";
        std::wcout << "Text: [";
        text->print();
        std::wcout<< "]" << std::endl;
    }

private:
    long long id;
    String<wchar_t>* title;
    String<wchar_t>* text;
    pos_type position;
};


#endif //NLP_DOCUMENT_H
