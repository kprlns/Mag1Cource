//
// Created by Никита on 07.06.2020.
//

#ifndef NLP_COMMON_H
#define NLP_COMMON_H

#include <ios>
#include <clocale>

struct DelimeterInteger : std::numpunct<wchar_t> {
    wchar_t do_thousands_sep() const { return L'\u200c'; }
    std::string do_grouping() const { return "~"; }
};

using pos_type = std::wstreampos ;


static const unsigned long long INITIAL_HASH_VALUE = 5381;
static inline unsigned long long djb2(unsigned long long currentHash, wchar_t c) {
    return
            (currentHash << 53)
            + (currentHash << 29)
            + (currentHash << 13)
            + (currentHash << 5)
            + currentHash
            + c;
}


#endif //NLP_COMMON_H
