#pragma once

// #include <boost/operators.hpp>
#include "recti.hpp"
#include <vector>

namespace recti
{

/**
 * @brief Rectilinear Polygon
 *
 * @tparam T
 */
template <typename T>
class rpolygon : public std::vector<point<T>>
{
  private:
    /**
     * @brief Construct a new rpolygon object
     *
     * @param pointset
     */
    rpolygon(std::vector<point<T>> pointset)
        : std::vector<point<T>> {std::move(pointset)}
    {
    }

  public:
    /**
     * @brief Create an x-monotone object
     *
     * @param pointset
     * @return rpolygon<T>
     */
    static rpolygon<T> create_xmonotone(std::vector<point<T>> pointset);

    /**
     * @brief Create a y-monotone object
     *
     * @param pointset
     * @return rpolygon<T>
     */
    static rpolygon<T> create_ymonotone(std::vector<point<T>> pointset);

    /**
     * @brief Create a regular object
     *
     * @param pointset
     * @return rpolygon<T>
     */
    static rpolygon<T> create_regular(std::vector<point<T>> pointset);

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
Stream& operator<<(Stream& out, const rpolygon<T>& r)
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
 * @return rpolygon<T>
 */
template <typename FwIter>
static void create_xmonotone_i(FwIter&& first, FwIter&& last)
{
    auto l2r = [](const auto& a, const auto& b) { return a.x() < b.x(); };
    auto r2l = [](const auto& a, const auto& b) { return b.x() < a.x(); };
    auto [min, max] = std::minmax_element(first, last, l2r);
    auto pivot = max->y();

    // using Fn = std::function<bool(const point<int>&)>;
    // Fn downup = [&pivot](const auto& a) { return a.y() < pivot; };
    // Fn updown = [&pivot](const auto& a) { return pivot < a.y(); };
    // auto middle =
    //     std::partition(first, last, (min->y() < pivot) ? downup : updown);
    FwIter middle;
    if (min->y() < pivot)
    {
        middle = std::partition(
            first, last, [&pivot](const auto& a) { return a.y() < pivot; });
    }
    else
    {
        middle = std::partition(
            first, last, [&pivot](const auto& a) { return pivot < a.y(); });
    }
    std::sort(first, middle, std::move(l2r));
    std::sort(middle, last, std::move(r2l));
}

/**
 * @brief
 *
 * @tparam T
 * @param pointset
 * @return rpolygon<T>
 */
template <typename T>
rpolygon<T> rpolygon<T>::create_xmonotone(std::vector<point<T>> pointset)
{
    create_xmonotone_i(pointset.begin(), pointset.end());
    return {std::move(pointset)};
}

/**
 * @brief
 *
 * @tparam T
 * @param pointset
 * @return rpolygon<T>
 */
template <typename T>
rpolygon<T> rpolygon<T>::create_ymonotone(std::vector<point<T>> pointset)
{
    using D = std::vector<dualpoint<T>>; // x <-> y
    auto first = reinterpret_cast<D&>(pointset).begin();
    auto last = reinterpret_cast<D&>(pointset).end();
    create_xmonotone_i(std::move(first), std::move(last));
    return {std::move(pointset)};
}


/**
 * @brief
 *
 * @tparam T
 * @param pointset
 * @return rpolygon<T>
 */
// template <typename FwIter>
// static void create_regular_recur(FwIter&& first, FwIter&& last)
// {
//     if (first == last) return;

//     auto l2r = [](const auto& a, const auto& b) { return a.x() < b.x(); };
//     auto r2l = [](const auto& a, const auto& b) { return b.x() < a.x(); };
//     auto [min, max] = std::minmax_element(first, last, l2r);
//     auto pivot = max->y();

//     using Fn = std::function<bool(const point<int>&)>;
//     Fn downup = [&pivot](const auto& a) { return a.y() < pivot; };
//     Fn updown = [&pivot](const auto& a) { return pivot < a.y(); };
//     auto middle =
//         std::partition(first, last, (min->y() < pivot) ? downup : updown);
//     create_regular_recur(first, middle, std::move(l2r));
//     create_regular_recur(middle, last, std::move(r2l));
// }

/**
 * @brief
 *
 * @tparam T
 * @param pointset
 * @return rpolygon<T>
 */
// template <typename FwIter>
// static void create_regular_i(FwIter&& first, FwIter&& last)
// {
//     auto l2r = [](const auto& a, const auto& b) { return a.x() < b.x(); };
//     auto r2l = [](const auto& a, const auto& b) { return b.x() < a.x(); };
//     auto [min, max] = std::minmax_element(first, last, l2r);
//     auto pivot = max->y();

//     using Fn = std::function<bool(const point<int>&)>;
//     Fn downup = [&pivot](const auto& a) { return a.y() < pivot; };
//     Fn updown = [&pivot](const auto& a) { return pivot < a.y(); };
//     auto middle =
//         std::partition(first, last, (min->y() < pivot) ? downup : updown);
//     create_regular_recur(first, middle, std::move(l2r));
//     create_regular_recur(middle, last, std::move(r2l));
// }

/**
 * @brief
 *
 * @tparam T
 * @param pointset
 * @return rpolygon<T>
 */
// template <typename T>
// rpolygon<T> rpolygon<T>::create_regular(std::vector<point<T>> pointset)
// {
//     using D = std::vector<dualpoint<T>>; // x <-> y
//     auto first = reinterpret_cast<D&>(pointset).begin();
//     auto last = reinterpret_cast<D&>(pointset).end();
//     create_regular_i(std::move(first), std::move(last));
//     return {std::move(pointset)};
// }

/**
 * @brief area
 *
 * @tparam T
 * @return T
 */
template <typename T>
T rpolygon<T>::area() const
{
    auto it = this->begin();
    assert(it != this->end());
    
    auto x0 = it->x();
    auto yi = it->y();
    ++it;

    auto sum = T {};
    for (; it != this->end(); ++it)
    {
        sum += (it->y() - yi) * (it->x() - x0), yi = it->y();
    }
    return sum;
}


} // namespace recti
