//
// Created by Никита on 07.06.2020.
//

#ifndef NLP_COMMON_H
#define NLP_COMMON_H

#include <ios>
#include <clocale>
#include <iostream>
#include <chrono>


struct DelimeterInteger : std::numpunct<wchar_t> {
    wchar_t do_thousands_sep() const { return L'\u200c'; }
    std::string do_grouping() const { return "~"; }
};

using pos_type = std::wstreampos ;


static const unsigned long long INITIAL_HASH_VALUE = 5381;
static inline unsigned long long djb2(unsigned long long currentHash, wchar_t c) {
    if(c == L'ё') {
        c = L'е';
    }
    return
            (currentHash << 53)
            + (currentHash << 29)
            + (currentHash << 13)
            + (currentHash << 5)
            + currentHash
            + c;
}

class Commons {
public:
    static void setLocale() {
        std::setlocale(LC_ALL, "");
        std::locale::global(std::locale("en_US.UTF-8"));
        std::ios_base::sync_with_stdio(false);
        std::setlocale(LC_ALL, "en_US.UTF-8");
        std::wcin.imbue(std::locale("en_US.UTF-8"));
        std::wcout.imbue(std::locale("en_US.UTF-8"));
        std::wcout.imbue(std::locale(std::wcin.getloc(), new DelimeterInteger));
    }

    static inline bool isSentenceSplitter(wchar_t c) {
        return c == L'.' || c == L'?' || c == L'!';
    }
};


#endif //NLP_COMMON_H
