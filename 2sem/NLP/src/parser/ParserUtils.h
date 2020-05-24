//
// Created by Никита on 23.05.2020.
//

#ifndef NLP_PARSERUTILS_H
#define NLP_PARSERUTILS_H

#include "myStl/String/String.h"

class ParserUtils {
public:

    static int findEntryForward(String<wchar_t>& string, wchar_t pattern, int entryNumber) {
        int cnt = 0;
        for(int i = 0; i < string.getSize(); ++i) {
            if(string[i] == pattern) {
                cnt++;
            }
            if(cnt == entryNumber) {
                return i;
            }
        }
        return -1;
    }
    static int findEntryBackward(String<wchar_t>& string, wchar_t pattern, int entryNumber) {
        int cnt = 0;
        for(int i = string.getSize() - 1; i >= 0; --i) {
            if(string[i] == pattern) {
                cnt++;
            }
            if(cnt == entryNumber) {
                return i;
            }
        }
        return -1;
    }

    static long long strToLong(String<wchar_t>& string) {
        long long result = 0;
        for(int i = 0; i < string.getSize(); ++i) {
            result += (string[i] - L'0');
            result *= 10;
        }
        return result;
    }

    static long long parsePageId(String<wchar_t>& string) {
        int start = 0;
        while(!(string[start] >= L'0' && string[start] <= L'9')) {
            start++;
        }
        long long result = 0;
        while(string[start] >= L'0' && string[start] <= L'9') {
            result += (string[start] - L'0');
            result *= 10;
            start++;
        }
        return result;
    }

    static String<wchar_t>* extractTextValue(String<wchar_t>& line) {
        return new String(
                line.substring(findEntryForward(line, L'"', 3) + 1,
                               findEntryBackward(line, L'"', 1)));
    }
    static String<wchar_t>* extractKey(String<wchar_t>& line) {
        return new String(
                line.substring(findEntryForward(line, L'"', 1) + 1,
                               findEntryForward(line, L'"', 2)));
    }

private:
};


#endif //NLP_PARSERUTILS_H
