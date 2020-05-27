set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -mtune=native")
add_executable(${BINARY}_run ${SOURCES} labs/nlp/lab1.cpp myStl/String/String.h myStl/Vector/Vector.h dto/Document.h parser/CorpusParser.h tokenization/Tokenization.h parser/ParserUtils.h)

add_library(${BINARY}_lib STATIC ${SOURCES} )