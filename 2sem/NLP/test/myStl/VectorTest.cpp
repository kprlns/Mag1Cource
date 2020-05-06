//
// Created by Никита on 02.05.2020.
//
#include "gtest/gtest.h"
#include "myStl/Vector/Vector.h"

TEST(VectorTest, testInitialVectorSize) {
    int size = 2;
    Vector<double> a = Vector<double>(size);
    EXPECT_EQ(a.getSize(), 0);
    EXPECT_EQ(a.getMaxSize(), size);
    EXPECT_EQ(typeid(a.getData()), typeid(double*));
}

TEST(VectorTest, VectorResizeOnAddTest) {
    int size = 0;
    Vector<int> a = Vector<int>(size);
    EXPECT_EQ(a.getSize(), 0);
    EXPECT_EQ(a.getMaxSize(), 0);
    a.add(0);
    EXPECT_EQ(a.getSize(), 1);
    EXPECT_EQ(a.getMaxSize(), 1);
}

TEST(VectorTest, VectorDoublesSizeOnAdd) {
    int size = 3;
    Vector<int> a = Vector<int>(size);
    a.add(0);
    EXPECT_EQ(a.getSize(), 1);
    EXPECT_EQ(a.getMaxSize(), 3);
    a.add(0);
    EXPECT_EQ(a.getSize(), 2);
    EXPECT_EQ(a.getMaxSize(), 3);
    a.add(0);
    EXPECT_EQ(a.getSize(), 3);
    EXPECT_EQ(a.getMaxSize(), 3);
    a.add(0);
    EXPECT_EQ(a.getSize(), 4);
    EXPECT_EQ(a.getMaxSize(), 6);
}

TEST(VectorTest, VectorResizeOnSet) {
    int size = 0;
    Vector<int> a = Vector<int>(size);

    a.set(0, 1);
    EXPECT_EQ(a.getSize(), 1);
    EXPECT_EQ(a.getMaxSize(), 1);

    a.set(1, 8);
    EXPECT_EQ(a.getSize(), 2);
    EXPECT_EQ(a.getMaxSize(), 2);


    a.set(4, 3);
    EXPECT_EQ(a.getSize(), 5);
    EXPECT_EQ(a.getMaxSize(), 8);

    EXPECT_EQ(a.get(0), 1);
    EXPECT_EQ(a.get(1), 8);
    EXPECT_EQ(a.get(4), 3);
}

TEST(VectorTest, VectorCopyConstructor) {
    int size = 1;
    Vector<long long> a(size);
    a.add(1);
    a.add(2);
    a.add(3);

    EXPECT_TRUE(a == Vector<long long>(a));
    EXPECT_EQ(a.getSize(), Vector<long long>(a).getSize());
}

TEST(VectorTest, TestDefaultOperatorEquality) {
    Vector<long long> a(2);
    a.add(1);
    a.add(1);
    a.add(1);
    auto b = Vector(a);
    b.set(2, 2);
    EXPECT_FALSE(a == b);
}

TEST(VectorTest, VectorMoveConstructor) {
    int a = 1;
    auto b = Vector<long long>(2);
}

TEST(VectorTest, MakeIntervalTest1) {
    int size = 1;
    Vector<long long> a(size);
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);

    Vector b = a.getInterval(0, a.getSize());
    EXPECT_TRUE(a == b);
}

TEST(VectorTest, MakeIntervalTest2) {
    int size = 1;
    Vector<long long> a(size);
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);

    Vector b = a.getInterval(2, a.getSize());
    EXPECT_EQ(b[0], 3);
    EXPECT_EQ(b[1], 4);
    EXPECT_EQ(b.getSize(), 2);
}

TEST(VectorTest, MakeIntervalTest3) {
    int size = 1;
    Vector<long long> a(size);
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);

    Vector b = a.getInterval(0, 2);
    EXPECT_EQ(b[0], 1);
    EXPECT_EQ(b[1], 2);
    EXPECT_EQ(b.getSize(), 2);
}

TEST(VectorTest, MakeIntervalTest4) {
    int size = 1;
    Vector<long long> a(size);
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);

    Vector b = a.getInterval(1, 2);
    EXPECT_EQ(b[0], 2);
    EXPECT_EQ(b.getSize(), 1);
}

TEST(VectorTest, MakeIntervalTest5) {
    int size = 1;
    Vector<long long> a(size);
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);

    Vector b = a.getInterval(1, 1);
    EXPECT_EQ(b.getSize(), 0);
}

TEST(VectorTest, TestRemove) {
    int size = 1;
    Vector<long long> a(size);
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);

    a.remove(0);
    EXPECT_EQ(a[0], 2);
    EXPECT_EQ(a[1], 3);
    EXPECT_EQ(a[2], 4);
    EXPECT_EQ(a.getSize(), 3);
}

TEST(VectorTest, TestRemove1) {
    int size = 1;
    Vector<long long> a(size);
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);

    a.remove(2);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 4);
    EXPECT_EQ(a.getSize(), 3);
}

TEST(VectorTest, TestRemove2) {
    int size = 1;
    Vector<long long> a(size);
    a.add(1);
    a.add(2);
    a.add(3);
    a.add(4);

    a.remove(3);
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_EQ(a[2], 3);
    EXPECT_EQ(a.getSize(), 3);
}