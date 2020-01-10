#include <catch2/catch.hpp>
#include <experimental/random>
#include <iostream>
#include <recti/recti.hpp>
#include <recti/rpolygon.hpp>
#include <vector>

using std::experimental::randint;
using namespace recti;
using std::cout;

TEST_CASE("Rectilinear Polygon test", "[test_rpolygon.cpp]")
{
    constexpr auto N = 100;
    auto S = std::vector<point<int>> {};
    S.reserve(N);

    for (auto i = 0U; i != N; ++i)
    {
        S.push_back({randint(-100, 99), randint(-100, 99)});
    }

    for (auto&& r : S)
    {
        cout << "  \\draw " << r << ";\n";
    }

    cout << "-------------------------------\n";

    auto R = rpolygon<int>::create_ymonotone(std::move(S));

    cout << R << "\n";
}
