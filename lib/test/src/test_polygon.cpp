#include <doctest/doctest.h>
#include <recti/polygon.hpp>
#include <recti/recti.hpp>
#include <vector>

// using std::randint;
using namespace recti;

TEST_CASE("Polygon test (y-mono)")
{
    auto S = std::vector<point<int>> {{-2, 2}, {0, -1}, {-5, 1}, {-2, 4},
        {0, -4}, {-4, 3}, {-6, -2}, {5, 1}, {2, 2}, {3, -3}, {-3, -4}, {1, 4}};

    create_ymono_polygon(S.begin(), S.end());
    auto P = polygon<int>(S);
    CHECK(P.signed_area_x2() == 102);
}

// 106980095362

TEST_CASE("Polygon test (x-mono)")
{
    auto S = std::vector<point<int>> {{-2, 2}, {0, -1}, {-5, 1}, {-2, 4},
        {0, -4}, {-4, 3}, {-6, -2}, {5, 1}, {2, 2}, {3, -3}, {-3, -4}, {1, 4}};
    create_xmono_polygon(S.begin(), S.end());
    auto P = polygon<int>(S);
    CHECK(P.signed_area_x2() == 110);
}
