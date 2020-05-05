//
// Created by Никита on 03.05.2020.
//

#include "gtest/gtest.h"
#include "myStl/String/String.h"

TEST(StringTest, ConstructorAndEqualsTest) {
    String<char> s("abc");
    EXPECT_TRUE(s == "abc");
}

TEST(StringTest, StringAddAndComparision) {
    String<char> a("a");
    String<char> b("b");
    //std::cout << a + b << "!!";
    EXPECT_TRUE(a + b == "ab");
}