#include <catch2/catch.hpp>
#include <experimental/random>
#include <iostream>
#include <list>
#include <recti/recti.hpp>
#include <set>

using std::experimental::randint;
using namespace recti;
using std::cout;

template <typename T>
struct my_point : point2D<T, T>
{
    double data;
};

TEST_CASE("Point test", "[test_recti.cpp]")
{
    auto a = my_point<int>{4, 8, 3.4};
    auto b = my_point<int>{5, 6, 1.0};

    CHECK(a < b);
}

TEST_CASE("Interval test", "[test_recti.cpp]")
{
    auto a = interval{4, 8};
    auto b = interval{5, 6};
    CHECK(a < 9);
    CHECK(a < 8.1);
    CHECK(3 < a);
    CHECK(not (a < b));
    CHECK(not (b < a));
    CHECK(a.contains(4));
    CHECK(a.contains(8));
    CHECK(a.contains(4.5));
    CHECK(a.contains(b));
}

TEST_CASE("Rectangle test", "[test_recti.cpp]")
{
    auto xrange1 = interval{4, 8};
    auto yrange1 = interval{5, 7};
    auto r1 = rectangle2D{xrange1, yrange1};
    auto xrange2 = interval{5, 7};
    auto yrange2 = interval{6, 6};
    auto r2 = rectangle2D{xrange2, yrange2};
    auto p = point2D{7.1, 6.0};

    CHECK(r1.contains(p));
    CHECK(r1.contains(r2));
}

TEST_CASE("Rectilinear test", "[test_recti.cpp]")
{
    auto lst = std::list<rectangle2D<int>> {};

    for (int i = 0; i < 10; ++i)
    {
        int ii = i * 100;
        for (int j = 0; j < 20; ++j)
        {
            int jj = j * 100;
            rectangle2D r {interval {ii, ii + randint(50, 110)},
                interval {jj, jj + randint(50, 110)}};
            lst.push_back(r);
        }
    }

    std::set<rectangle2D<int>> S;  // set of maximal non-overlapped rectangles
    std::list<rectangle2D<int>> L; // list of the removed rectangles

    for (const auto& r : lst)
    {
        auto search = S.find(r);
        if (search != S.end())
        {
            L.push_back(r);
        }
        else
        {
            S.insert(r);
        }
    }

    // for (const auto& r : S)
    // {
    //     cout << "  \\draw " << r << ";\n";
    // }
    // for (const auto& r : L)
    // {
    //     cout << "  \\draw[color=red] " << r << ";\n";
    // }
}
