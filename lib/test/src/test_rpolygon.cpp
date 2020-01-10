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

    auto first = S.begin();
    auto last = S.end();
    auto l2r = [](const auto& a, const auto& b) { return a.x() < b.x(); };
    auto r2l = [](const auto& a, const auto& b) { return a.x() > b.x(); };
    auto [min, max] = std::minmax_element(first, last, l2r);
    auto pivot = max->y();

    using Fn = std::function<bool(const point<int>&)>;
    Fn downup = [&pivot](const auto& a) { return a.y() < pivot; };
    Fn updown = [&pivot](const auto& a) { return a.y() > pivot; };
    auto middle =
        std::partition(first, last, (min->y() < pivot) ? downup : updown);
    std::sort(first, middle, std::move(l2r));
    std::sort(middle, last, std::move(r2l));

    for (auto&& r : S)
    {
        cout << "  \\draw " << r << ";\n";
    }
}
