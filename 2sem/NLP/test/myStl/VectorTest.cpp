//
// Created by Никита on 02.05.2020.
//
#include "gtest/gtest.h"
#include "myStl/Vector/Vector.h"


TEST(VectorTest, test1) {
    Vector<int> a = Vector<int>();
    EXPECT_EQ(a.getSize(), 11);
}