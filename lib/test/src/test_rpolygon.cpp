#include <doctest.h>
// #include <random>
#include <iostream>
#include <recti/recti.hpp>
#include <recti/rpolygon.hpp>
#include <vector>

// using std::randint;
using namespace recti;
using std::cout;

TEST_CASE("Rectilinear Polygon test")
{
    constexpr auto N = 100;
    auto S = std::vector<point<int>> {};
    S.reserve(N);

    for (auto i = 0U; i != N; ++i)
    {
        // S.emplace_back(point<int>{randint(-100, 100), randint(-100, 100)});
        S.emplace_back(point<int> {std::rand() % 100, std::rand() % 100});
    }

    // for (auto&& r : S)
    // {
    //     cout << "  \\draw " << r << ";\n";
    // }

    // cout << "-------------------------------\n";
    // auto R1 = rpolygon<int>::create_xmonotone(S);
    // cout << R1.area() << "\n";

    // cout << "-------------------------------\n";
    // auto R2 = rpolygon<int>::create_ymonotone(S);
    // cout << R2.area() << "\n";
}
