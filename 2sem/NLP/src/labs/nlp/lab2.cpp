//
// Created by kprlns on 16.06.2020.
//

#include <index/Indexer.h>
#include <climits>
#include <clocale>
#include <locale>
#include <query/FileQueriesProcessor.h>

#include "parser/CorpusParser.h"
#include "index/IndexLoader.h"
#include "query/QueryService.h"
#include "Common.h"

#include <vector>
#include <algorithm>

#include "tokenization/ZiphStatistics.h"


int main() {
    Commons::setLocale();

    ZiphStatistics().calc();
    return 0;
}