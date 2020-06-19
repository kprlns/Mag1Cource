//
// Created by Никита on 12.06.2020.
//

#include <query/Query.h>
#include <query/QueryParser.h>
#include "gtest/gtest.h"
#include "myStl/String.h"
#include "myStl/HashSet.h"
#include "Common.h"

void setLocaleQ() {
    std::setlocale(LC_ALL, "");
    std::locale::global(std::locale("en_US.UTF-8"));
    std::ios_base::sync_with_stdio(false);
    std::setlocale(LC_ALL, "en_US.UTF-8");
    std::wcin.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale("en_US.UTF-8"));
    std::wcout.imbue(std::locale(std::wcin.getloc(), new DelimeterInteger));
}


TEST(QueryTest, test1) {
    setLocaleQ();


    String<wchar_t> str(L"московский авиационный институт");

    Query* query = QueryParser().parse(&str, new HashSet<unsigned long long>(100));
    query->print();

    EXPECT_EQ(query->getQuery()->getSize(), 5);
    EXPECT_TRUE(query->getQuery()->get(0)->getItemType() == OPERAND);
    EXPECT_TRUE(query->getQuery()->get(1)->getItemType() == AND_OPERATOR);
    EXPECT_TRUE(query->getQuery()->get(2)->getItemType() == OPERAND);
    EXPECT_TRUE(query->getQuery()->get(3)->getItemType() == AND_OPERATOR);
    EXPECT_TRUE(query->getQuery()->get(4)->getItemType() == OPERAND);
}

TEST(QueryTest, test2) {
    Commons::setLocale();


    String<wchar_t> str(L"(Красный | Желтый) автомобиль");

    Query* query = QueryParser().parse(&str, new HashSet<unsigned long long>(100));
    query->print();

    EXPECT_EQ(query->getQuery()->getSize(), 7);
    EXPECT_TRUE(query->getQuery()->get(0)->getItemType() == OPEN_PARENTHESIS);
    EXPECT_TRUE(query->getQuery()->get(1)->getItemType() == OPERAND);
    EXPECT_TRUE(query->getQuery()->get(2)->getItemType() == OR_OPERATOR);
    EXPECT_TRUE(query->getQuery()->get(3)->getItemType() == OPERAND);
    EXPECT_TRUE(query->getQuery()->get(4)->getItemType() == CLOSE_PARENTHESIS);
    EXPECT_TRUE(query->getQuery()->get(5)->getItemType() == AND_OPERATOR);
    EXPECT_TRUE(query->getQuery()->get(6)->getItemType() == OPERAND);
}

TEST(QueryTest, test3) {
    Commons::setLocale();


    String<wchar_t> str(L"руки !ноги");

    Query* query = QueryParser().parse(&str, new HashSet<unsigned long long>(100));
    query->print();

    EXPECT_EQ(query->getQuery()->getSize(), 4);
    EXPECT_TRUE(query->getQuery()->get(0)->getItemType() == OPERAND);
    EXPECT_TRUE(query->getQuery()->get(1)->getItemType() == AND_OPERATOR);
    EXPECT_TRUE(query->getQuery()->get(2)->getItemType() == NEGATE_OPERATOR);
    EXPECT_TRUE(query->getQuery()->get(3)->getItemType() == OPERAND);

}