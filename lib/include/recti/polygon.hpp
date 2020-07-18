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
    polygon(std::vector<point<T>> pointset)
        : std::vector<point<T>> {std::move(pointset)}
    {
    }

  public:
    template <typename FwIter>
    static void create_ymono_polygon(FwIter&& first, FwIter&& last);

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
    auto upward = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) < std::tie(b.y(), b.x()); };
    auto min_it = std::min_element(first, last, upward);
    auto max_it = std::max_element(first, last, upward);
    auto dx = max_it->x() - min_it->x();
    auto dy = max_it->y() - min_it->y();
    auto middle = std::partition(first, last, [&](const auto& a) {
        return dx * (a.y() - min_it->y()) < (a.x() - min_it->x()) * dy;
    });

    auto downward = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) > std::tie(b.y(), b.x()); };
    std::sort(first, middle, std::move(upward));
    std::sort(middle, last, std::move(downward));
}


} // namespace recti
