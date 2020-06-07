//
// Created by Никита on 06.06.2020.
//

#include <index/Indexer.h>

int main() {
    String<wchar_t>* testStr = new String(L"a~b.– n' c-d,e.f?g![]АБВГДабвгд↑/\n");
    for(int i = 0; i < testStr->getSize(); ++i) {
        std::wcout << i << " ";
        std::wcout << (*testStr)[i] << L" " << (unsigned long long) (*testStr)[i] << ": " << std::boolalpha
                   << (iswalnum((*testStr)[i]) != 0) << std::endl;
    }
    return 0;

    Index* index = Indexer().indexFile("/Users/kprlns/Desktop/Mag1Cource/2sem/NLP/docs/dataUkrainianGamesCut.json");
    index->printIndex();
    return 0;
}