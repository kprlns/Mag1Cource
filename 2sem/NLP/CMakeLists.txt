cmake_minimum_required(VERSION 3.16)
project(NLP)

set(CMAKE_CXX_STANDARD 17)


include_directories(src)
include_directories(test)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(lib/googletest)


add_executable(NLP main.cpp src/myStl/Vector/Vector.h src/myStl/String/String.h src/dto/Document.h src/parser/CorpusParser.h)


