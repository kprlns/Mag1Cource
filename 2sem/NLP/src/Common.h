//
// Created by Никита on 07.06.2020.
//

#ifndef NLP_COMMON_H
#define NLP_COMMON_H

#include <ios>

struct DelimeterInteger : std::numpunct<wchar_t> {
    wchar_t do_thousands_sep() const { return L'\u200c'; }
    std::string do_grouping() const { return "~"; }
};

using pos_type = std::wstreampos ;



#endif //NLP_COMMON_H
