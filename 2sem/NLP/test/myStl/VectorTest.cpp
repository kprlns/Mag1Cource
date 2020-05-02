//
// Created by Никита on 02.05.2020.
//
#include "gtest/gtest.h"
#include "myStl/Vector/Vector.h"


TEST(VectorTest, test1) {
    int size = 2;
    Vector<int> a = Vector<int>(2);
    EXPECT_EQ(a.getSize(), size);
}