//
// Created by kprlns on 19.06.2020.
//

#include "gtest/gtest.h"

#include "myStl/Vector.h"
#include "compression/VariableByte.h"

template<typename T>
void printMyVector(Vector<T>* vec) {
    for(int i = 0; i < vec->getSize(); ++i) {
        std::wcout << vec->get(i) << L" ";
    }
    std::wcout << std::endl;
}

TEST(VariableByteTest, test1) {
    VariableByte variableByte;
    int arr[20] = {1, 256 ,1239, 329, 64, 32, 128, 256, 23894239, 29384, 198943};
    Vector<int>* testVector = new Vector<int>(arr, 11);
    Vector<int>* res = new Vector<int>(64);

    Vector<unsigned char>* encoded = variableByte.encode(testVector, new Vector<unsigned char>(16));
    res = variableByte.decode(encoded, res);

    printMyVector(testVector);
    printMyVector(encoded);
    printMyVector(res);

    EXPECT_TRUE(*testVector == *res);
}