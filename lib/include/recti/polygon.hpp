#pragma once

// #include <boost/operators.hpp>
#include "recti.hpp"
#include <vector>

namespace recti
{

/**
 * @brief Polygon
 *
 * @tparam T
 */
template <typename T>
class polygon
{
  private:
    point<T> _origin;
    std::vector<vector2<T>> _vecs;

  public:
    /**
     * @brief Construct a new polygon object
     *
     * @param pointset
     */
    explicit constexpr polygon(const std::vector<point<T>>& pointset)
        : _origin {pointset[0]}
    {
        for (auto i = 1U; i != pointset.size(); ++i)
        {
            this->_vecs.push_back(pointset[i] - this->_origin);
        }
    }

    /**
     * @brief
     *
     * @param rhs
     * @return constexpr point&
     */
    constexpr auto operator+=(const vector2<T>& rhs) -> polygon&
    {
        this->_origin += rhs;
        return *this;
    }

    /**
     * @brief
     *
     * @return T
     */
    constexpr auto signed_area_x2() const -> T
    {
        auto&& vs = this->_vecs;
        auto n = this->_vecs.size();
        auto res = vs[0].x() * vs[1].y() - vs[n - 1].x() * vs[n - 2].y();
        for (auto i = 1U; i != n - 1; ++i)
        {
            res += vs[i].x() * (vs[i + 1].y() - vs[i - 1].y());
        }
        return res;
    }

    /**
     * @brief
     *
     * @tparam U
     * @param rhs
     * @return true
     * @return false
     */
    template <typename U>
    auto contains(const point<U>& rhs) const -> bool;

    /**
     * @brief
     *
     * @return point<T>
     */
    auto lower() const -> point<T>;

    /**
     * @brief
     *
     * @return point<T>
     */
    auto upper() const -> point<T>;
};

/**
 * @brief
 *
 * @tparam Stream
 * @tparam T
 * @param out
 * @param r
 * @return Stream&
 */
template <class Stream, typename T>
auto operator<<(Stream& out, const polygon<T>& r) -> Stream&
{
    for (auto&& p : r)
    {
        out << "  \\draw " << p << ";\n";
    }
    return out;
}

} // namespace recti

#include <algorithm>
#include <functional>
#include <numeric> // import accumulate

namespace recti
{

/**
 * @brief Create a ymono polygon object
 *
 * @tparam FwIter
 * @param first
 * @param last
 */
template <typename FwIter>
inline void create_ymono_polygon(FwIter&& first, FwIter&& last)
{
    auto up = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) < std::tie(b.y(), b.x());
    };
    auto down = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) > std::tie(b.y(), b.x());
    };
    auto topmost = *std::max_element(first, last, up);
    auto botmost = *std::min_element(first, last, up);
    auto d = topmost - botmost;
    auto r2l = [&](const auto& a) { return d.cross(a - botmost) <= 0; };
    auto middle = std::partition(first, last, std::move(r2l));
    std::sort(first, middle, std::move(up));
    std::sort(middle, last, std::move(down));
}


/**
 * @brief Create a xmono polygon object
 *
 * @tparam FwIter
 * @param first
 * @param last
 */
template <typename FwIter>
inline void create_xmono_polygon(FwIter&& first, FwIter&& last)
{
    const auto leftmost = *std::min_element(first, last);
    const auto rightmost = *std::max_element(first, last);
    const auto d = rightmost - leftmost;
    auto r2l = [&](const auto& a) { return d.cross(a - leftmost) <= 0; };
    const auto middle = std::partition(first, last, std::move(r2l));
    std::sort(first, middle);
    std::sort(middle, last, std::greater<>());
}

// template <typename T>
// template <typename FwIter>
// void polygon<T>::create_test_polygon(FwIter&& first, FwIter&& last)
// {
//     auto up = [](const auto& a, const auto& b) {
//         return std::tie(a.y(), a.x()) < std::tie(b.y(), b.x());
//     };
//     auto down = [](const auto& a, const auto& b) {
//         return std::tie(a.y(), a.x()) > std::tie(b.y(), b.x());
//     };
//     auto left = [](const auto& a, const auto& b) {
//         return std::tie(a.x(), a.y()) < std::tie(b.x(), b.y());
//     };
//     auto right = [](const auto& a, const auto& b) {
//         return std::tie(a.x(), a.y()) > std::tie(b.x(), b.y());
//     };

//     auto min_pt = *std::min_element(first, last, up);
//     auto max_pt = *std::max_element(first, last, up);
//     auto dx = max_pt.x() - min_pt.x();
//     auto dy = max_pt.y() - min_pt.y();
//     auto middle = std::partition(first, last, [&](const auto& a) {
//         return dx * (a.y() - min_pt.y()) < (a.x() - min_pt.x()) * dy;
//     });

//     auto max_pt1 = *std::max_element(first, middle, left);
//     auto middle2 = std::partition(
//         first, middle, [&](const auto& a) { return a.y() < max_pt1.y(); });

//     auto min_pt2 = *std::min_element(middle, last, left);
//     auto middle3 = std::partition(
//         middle, last, [&](const auto& a) { return a.y() > min_pt2.y(); });

//     if (dx < 0) // clockwise
//     {
//         std::sort(first, middle2, down);
//         std::sort(middle2, middle, left);
//         std::sort(middle, middle3, up);
//         std::sort(middle3, last, right);
//     }
//     else // anti-clockwise
//     {
//         std::sort(first, middle2, left);
//         std::sort(middle2, middle, up);
//         std::sort(middle, middle3, right);
//         std::sort(middle3, last, down);
//     }
// }

} // namespace recti
