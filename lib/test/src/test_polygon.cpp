#include <doctest/doctest.h>
#include <iostream>
#include <recti/polygon.hpp>
#include <recti/recti.hpp>
#include <vector>

// using std::randint;
using namespace recti;
using std::cout;

TEST_CASE("Polygon test")
{
    auto S = std::vector<point<int>> {{-2, 2}, {0, -1}, {-5, 1}, {-2, 4},
        {0, -4}, {-4, 3}, {-6, -2}, {5, 1}, {2, 2}, {3, -3}, {-3, -4}, {1, 4}};

    cout << "-------------------------------\n";
    // polygon<int>::create_test_polygon(S.begin(), S.end());

    for (auto&& p : S)
    {
        std::cout << "  \\draw " << p << ";\n";
    }
}
