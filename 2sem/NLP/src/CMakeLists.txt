set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native")

set(MY_SRC
        myStl/String.h
        myStl/Vector.h
        dto/Document.h
        parser/CorpusParser.h
        tokenization/Tokenization.h
        parser/ParserUtils.h
        myStl/Pair.h
        myStl/HashSet.h
        index/BucketIndex.h index/IndexSaver.h index/IndexLoader.h
        labs/is/lab4.cpp
        query/Query.h query/QueryItem.h query/QueryParser.h query/QueryProcessor.h)

add_executable(${BINARY}_run ${SOURCES} labs/nlp/lab1.cpp ${MY_SRC})
add_executable(${BINARY}_run_is_lab3 ${SOURCES} labs/is/lab3.cpp ${MY_SRC})



add_library(${BINARY}_lib STATIC ${SOURCES} index/Indexer.h index/Index.h Common.h myStl/HashMap.h index/IndexSaver.h)