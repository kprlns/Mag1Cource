//
// Created by kprlns on 05.06.2020.
//
#include "gtest/gtest.h"
#include "myStl/HashSet.h"
#include "myStl/Vector.h"

TEST(HashSetTest, testBinarySearch) {
    auto vec = new Vector<int>(10);
    vec->add(1);
    vec->add(3);
    vec->add(5);
    vec->add(10);
    vec->add(40);

    auto set = HashSet(vec);
    int start = 0;

    std::wcout << set.binarySearch(0 , &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(1 , &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(2 , &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(3 , &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(4 , &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(5 , &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(6 , &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(10, &start) << " " << start << std::endl;
    std::wcout << set.binarySearch(20, &start) << " " << start << std::endl;
    std::wcout << set.binarySearch(40, &start) << " " << start << std::endl;
    std::wcout << set.binarySearch(50, &start) << " " << start << std::endl;
    //delete vec;
}

TEST(HashSetTest, testBinarySearch1) {
    auto vec = new Vector<int>(10);
    vec->add(1);
    vec->add(3);
    vec->add(5);
    vec->add(10);
    vec->add(20);
    vec->add(40);

    auto set = HashSet(vec);
    int start = 0;

    std::wcout << set.binarySearch(0, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(1, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(2, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(3, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(4, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(5, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(6, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(10, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(12, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(20, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(25, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(40, &start)  << " " << start << std::endl;
    std::wcout << set.binarySearch(50, &start)  << " " << start << std::endl;
    //delete vec;
}

TEST(HashSetTest, testPut) {
    HashSet<unsigned long long> set(32);
    set.put(5);
    set.put(1);
    set.put(3);
    set.put(2);
    set.put(5);
    set.put(4);

    int res;

    EXPECT_EQ(set.getSize(), 5);
    EXPECT_EQ(*set.get(1, &res), 1);
    EXPECT_EQ(*set.get(2, &res), 2);
    EXPECT_EQ(*set.get(3, &res), 3);
    EXPECT_EQ(*set.get(4, &res), 4);
    EXPECT_EQ(*set.get(5, &res), 5);
    EXPECT_EQ(*set.get(0, &res), nullptr);
    EXPECT_EQ(*set.get(10,&res), nullptr);
}