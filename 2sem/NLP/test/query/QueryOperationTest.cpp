//
// Created by Никита on 13.06.2020.
//

#include "gtest/gtest.h"
#include "myStl/Vector.h"
#include "query/QueryOperation.h"

TEST(QueryOperationTest, intersectTest) {
    const int array1[] = {2, 4, 6, 7, 9, 12};
    const int array2[] = {3, 4, 5, 6, 7, 10, 12};
    Vector<int> vector1(16);
    vector1.addAll(array1, 6);

    Vector<int> vector2(16);
    vector2.addAll(array2, 7);

    Vector<int>* res = QueryOperation().intersect(&vector1, &vector2);
    EXPECT_EQ(res->getSize(), 4);
    EXPECT_EQ(res->get(0), 4);
    EXPECT_EQ(res->get(1), 6);
    EXPECT_EQ(res->get(2), 7);
    EXPECT_EQ(res->get(3), 12);
}

TEST(QueryOperationTest, unionTest) {
    const int array1[] = {2, 4, 6, 7, 9, 12};
    const int array2[] = {2, 3, 4, 5, 6, 7, 10, 12};
    Vector<int> vector1(16);
    vector1.addAll(array1, 6);

    Vector<int> vector2(16);
    vector2.addAll(array2, 8);

    Vector<int>* res = QueryOperation().unite(&vector1, &vector2);
    EXPECT_EQ(res->getSize(), 9);
    EXPECT_EQ(res->get(0), 2);
    EXPECT_EQ(res->get(1), 3);
    EXPECT_EQ(res->get(2), 4);
    EXPECT_EQ(res->get(3), 5);
    EXPECT_EQ(res->get(4), 6);
    EXPECT_EQ(res->get(5), 7);
    EXPECT_EQ(res->get(6), 9);
    EXPECT_EQ(res->get(7), 10);
    EXPECT_EQ(res->get(8), 12);
}

TEST(QueryOperationTest, negateTest) {
    const int array2[] = {0, 3, 4, 6, 7, 10, 12};

    Vector<int> vector2(16);
    vector2.addAll(array2, 7);

    Vector<int>* res = QueryOperation().negate(&vector2, 15);
    EXPECT_EQ(res->getSize(), 8);
    EXPECT_EQ(res->get(0), 1);
    EXPECT_EQ(res->get(1), 2);
    EXPECT_EQ(res->get(2), 5);
    EXPECT_EQ(res->get(3), 8);
    EXPECT_EQ(res->get(4), 9);
    EXPECT_EQ(res->get(5), 11);
    EXPECT_EQ(res->get(6), 13);
    EXPECT_EQ(res->get(7), 14);
}