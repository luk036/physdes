#include <doctest/doctest.h>
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
    auto S = std::vector<point<int>> {{-2, 2}, {0, -1}, {-5, 1}, {-2, 4},
        {0, -4}, {-4, 3}, {-6, -2}, {5, 1}, {2, 2}, {3, -3}, {-3, -4}, {1, 4}};

    cout << "-------------------------------\n";
    create_ymono_rpolygon(S.begin(), S.end());
    auto P = rpolygon<int>(S);
    CHECK(P.signed_area() == 52);

    // for (auto&& p : S)
    // {
    //     std::cout << "  \\draw " << p << ";\n";
    // }
}
