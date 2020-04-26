/*
 *  Distributed under the MIT License (See accompanying file /LICENSE )
 */
#include "recti/fractions.hpp"
// #include <boost/multiprecision/cpp_int.hpp>
#include <doctest.h>
#include <iostream>

using namespace fun;

TEST_CASE("undefined behavior")
{
    int a = 125;
    int c = 32;
    int b = a >> c; // see if your tool can catch the problem
    std::cout << "125 >> 32 = " << b << "\n";
}

TEST_CASE("Fraction")
{
    // using boost::multiprecision::cpp_int;
    // static_assert(Integral<cpp_int>);

    const auto a = 3;
    const auto b = 4;
    const auto c = 5;
    const auto d = 6;
    // const auto f = -30;
    // const auto g = 4;
    // const auto z = 0;
    // const auto h = -g;

    const auto p = Fraction {a, b};
    std::cout << p << '\n';
    const auto q = Fraction {c, d};

    CHECK(p == Fraction(30, 40));
    CHECK(p + q == Fraction(19, 12));
    CHECK(p - q == Fraction(-1, 12));
    CHECK(p < q);
    CHECK(p > 0);
}

TEST_CASE("Fraction Special Cases")
{
    const auto p = Fraction {3, 4};
    const auto inf = Fraction {1, 0};
    const auto nan = Fraction {0, 0};
    const auto zero = Fraction {0, 1};

    CHECK(-inf < zero);
    CHECK(zero < inf);
    CHECK(-inf < p);
    CHECK(p < inf);
    CHECK(inf == inf);
    CHECK(-inf < inf);
    CHECK(inf == inf * p);
    CHECK(inf == inf * inf);
    CHECK(inf == p / zero);
    CHECK(inf == inf / zero);
    CHECK(nan == nan);
    CHECK(nan == inf * zero);
    CHECK(nan == -inf * zero);
    CHECK(nan == inf / inf);
    CHECK(nan == nan * zero);
    CHECK(nan == nan * nan);
    CHECK(inf == inf + inf);
    CHECK(nan == inf - inf);
    CHECK( inf + p == inf ); // ???
    CHECK( -inf + p == -inf ); // ???
}
