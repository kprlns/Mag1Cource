//
// Created by Никита on 03.05.2020.
//

#include "gtest/gtest.h"
#include "myStl/String.h"
#include <locale>

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

TEST(StringTest, TrimTest) {
    String<char> a("\nabc rk\nfw \t adl,l;  \n\t");
    a.trim();
    EXPECT_TRUE(a == "abc rk\nfw \t adl,l;");
}

TEST(StringTest, SubstringTrst) {
    String<char> a("abcde");
    EXPECT_TRUE((*a.substring(0, 2)) == "ab");
    EXPECT_TRUE((*a.substring(2, 3)) == "c");
    EXPECT_TRUE((*a.substring(1, 3)) == "bc");
    EXPECT_TRUE((*a.substring(2, 5)) == "cde");
    EXPECT_TRUE(a == "abcde");
}

TEST(StringTest, SplitTest) {
    String<char> a("aaa bbb  cc    d ");
    auto splitted = a.split(' ');
    EXPECT_EQ(splitted->getSize(), 4);
    EXPECT_TRUE(*(*splitted)[0] == "aaa");
    EXPECT_TRUE(*(*splitted)[1] == "bbb");
    EXPECT_TRUE(*(*splitted)[2] == "cc");
    EXPECT_TRUE(*(*splitted)[3] == "d");
}

TEST(StringTest, SplitTest1) {
    std::wcout << L"-----------------------\n";
    String<char> a("aaa bbb");
    auto splitted = a.split(' ');
    EXPECT_EQ(splitted->getSize(), 2);
    EXPECT_TRUE(*(*splitted)[0] == "aaa");
    EXPECT_TRUE(*(*splitted)[1] == "bbb");
    std::wcout << L"-----------------------\n";

}

TEST(StringTest, SplitTest2) {
    String<char> a("aaa:");
    auto splitted = a.split(':');
    EXPECT_EQ(splitted->getSize(), 1);
    EXPECT_TRUE(*(*splitted)[0] == "aaa");
}















