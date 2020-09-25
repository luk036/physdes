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
class polygon : public std::vector<point<T>>
{
  private:
    /**
     * @brief Construct a new polygon object
     *
     * @param pointset
     */
    explicit polygon(std::vector<point<T>>&& pointset) noexcept
        : std::vector<point<T>> {std::move(pointset)}
    {
    }

    /**
     * @brief Construct a new polygon object
     *
     * @param pointset
     */
    explicit polygon(const std::vector<point<T>>& pointset)
        : std::vector<point<T>> {std::move(pointset)}
    {
    }

  public:
    /**
     * @brief Create a ymono polygon object
     *
     * @tparam FwIter
     * @param first
     * @param last
     */
    template <typename FwIter>
    static void create_ymono_polygon(FwIter&& first, FwIter&& last);

    /**
     * @brief Create a test polygon object
     *
     * @tparam FwIter
     * @param first
     * @param last
     */
    template <typename FwIter>
    static void create_test_polygon(FwIter&& first, FwIter&& last);

    /**
     * @brief Create a y-monotone object
     *
     * @param pointset
     * @return polygon<T>
     */
    static polygon<T> create_ymonotone(std::vector<point<T>> pointset);

    /**
     * @brief Create an x-monotone object
     *
     * @param pointset
     * @return polygon<T>
     */
    static polygon<T> create_xmonotone(std::vector<point<T>> pointset);

    /**
     * @brief Create a regular object
     *
     * @param pointset
     * @return polygon<T>
     */
    static polygon<T> create_regular(std::vector<point<T>> pointset);

    /**
     * @brief area
     *
     * @return auto
     */
    T area() const;

    /**
     * @brief
     *
     * @tparam U
     * @param rhs
     * @return true
     * @return false
     */
    template <typename U>
    bool contains(const point<U>& rhs) const;

    /**
     * @brief
     *
     * @return point<T>
     */
    point<T> lower() const;

    /**
     * @brief
     *
     * @return point<T>
     */
    point<T> upper() const;
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
Stream& operator<<(Stream& out, const polygon<T>& r)
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
 * @brief
 *
 * @tparam T
 * @param pointset
 * @return polygon<T>
 */
template <typename T>
template <typename FwIter>
void polygon<T>::create_ymono_polygon(FwIter&& first, FwIter&& last)
{
    auto up = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) < std::tie(b.y(), b.x());
    };
    auto min_pt = *std::min_element(first, last, up);
    auto max_pt = *std::max_element(first, last, up);
    auto dx = max_pt.x() - min_pt.x();
    auto dy = max_pt.y() - min_pt.y();
    auto middle = std::partition(first, last, [&](const auto& a) {
        return dx * (a.y() - min_pt.y()) < (a.x() - min_pt.x()) * dy;
    });

    auto down = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) > std::tie(b.y(), b.x());
    };
    std::sort(first, middle, up);
    std::sort(middle, last, down);
}

/**
 * @brief
 *
 * @tparam T
 * @param pointset
 * @return polygon<T>
 */
template <typename T>
template <typename FwIter>
void polygon<T>::create_test_polygon(FwIter&& first, FwIter&& last)
{
    auto up = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) < std::tie(b.y(), b.x());
    };
    auto down = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) > std::tie(b.y(), b.x());
    };
    auto left = [](const auto& a, const auto& b) {
        return std::tie(a.x(), a.y()) < std::tie(b.x(), b.y());
    };
    auto right = [](const auto& a, const auto& b) {
        return std::tie(a.x(), a.y()) > std::tie(b.x(), b.y());
    };

    auto min_pt = *std::min_element(first, last, up);
    auto max_pt = *std::max_element(first, last, up);
    auto dx = max_pt.x() - min_pt.x();
    auto dy = max_pt.y() - min_pt.y();
    auto middle = std::partition(first, last, [&](const auto& a) {
        return dx * (a.y() - min_pt.y()) < (a.x() - min_pt.x()) * dy;
    });

    auto max_pt1 = *std::max_element(first, middle, left);
    auto middle2 = std::partition(
        first, middle, [&](const auto& a) { return a.y() < max_pt1.y(); });

    auto min_pt2 = *std::min_element(middle, last, left);
    auto middle3 = std::partition(
        middle, last, [&](const auto& a) { return a.y() > min_pt2.y(); });

    if (dx < 0) // clockwise
    {
        std::sort(first, middle2, down);
        std::sort(middle2, middle, left);
        std::sort(middle, middle3, up);
        std::sort(middle3, last, right);
    }
    else // anti-clockwise
    {
        std::sort(first, middle2, left);
        std::sort(middle2, middle, up);
        std::sort(middle, middle3, right);
        std::sort(middle3, last, down);
    }
}

} // namespace recti
