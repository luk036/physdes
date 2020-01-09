#include <algorithm>
#include <catch2/catch.hpp>
#include <experimental/random>
#include <functional>
#include <iostream>
#include <recti/recti.hpp>
#include <vector>

using std::experimental::randint;
using namespace recti;
using std::cout;

TEST_CASE("Rectilinear Polygon test", "[test_rpolygon.cpp]")
{
    auto S = std::vector<point2D<int>> {};

    for (auto i = 0U; i != 100; ++i)
    {
        S.push_back({randint(-100, 99), randint(-100, 99)});
    }

    for (auto&& r : S)
    {
        cout << "  \\draw " << r << ";\n";
    }

    cout << "-------------------------------\n";

    auto first = S.begin();
    auto last = S.end();
    auto l2r = [](const auto& a, const auto& b) { return a._x < b._x; };
    auto r2l = [](const auto& a, const auto& b) { return a._x > b._x; };
    auto [min, max] = std::minmax_element(first, last, l2r);
    auto pivot = max->_y;

    using Fn = std::function<bool(const point2D<int>&)>;
    Fn downup = [&pivot](const auto& a) { return a._y < pivot; };
    Fn updown = [&pivot](const auto& a) { return a._y > pivot; };
    auto middle =
        std::partition(first, last, (min->_y < pivot) ? downup : updown);
    std::sort(first, middle, std::move(l2r));
    std::sort(middle, last, std::move(r2l));

    for (auto&& r : S)
    {
        cout << "  \\draw " << r << ";\n";
    }
}
