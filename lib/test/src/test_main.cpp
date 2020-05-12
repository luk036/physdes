// -*- coding: utf-8 -*-
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("undefined behavior")
{
    int a = 125;
    int c = 32;
    int b = a >> c; // see if your tool can catch the problem
    std::cout << "125 >> 32 = " << b << "\n";
}

TEST_CASE("sizeof")
{
    CHECK(sizeof(int) == 4);
    CHECK(sizeof(size_t) == 8);
}
