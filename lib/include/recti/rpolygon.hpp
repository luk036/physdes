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
    explicit rpolygon(std::vector<point<T>>&& pointset) noexcept
        : std::vector<point<T>> {std::move(pointset)}
    {
    }

    /**
     * @brief Construct a new rpolygon object
     *
     * @param pointset
     */
    explicit rpolygon(const std::vector<point<T>>& pointset)
        : std::vector<point<T>> {pointset}
    {
    }

  public:
    /**
     * @brief Create a ymono rpolygon object
     *
     * @tparam FwIter
     * @param first
     * @param last
     */
    template <typename FwIter>
    static void create_ymono_rpolygon(FwIter&& first, FwIter&& last);

    /**
     * @brief Create a test rpolygon object
     *
     * @tparam FwIter
     * @param first
     * @param last
     */
    template <typename FwIter>
    static void create_test_rpolygon(FwIter&& first, FwIter&& last);

    /**
     * @brief Create an x-monotone object
     *
     * @param pointset
     * @return rpolygon<T>
     */
    static auto create_xmonotone(std::vector<point<T>>&& pointset) -> rpolygon<T>;

    /**
     * @brief Create a y-monotone object
     *
     * @param pointset
     * @return rpolygon<T>
     */
    static auto create_ymonotone(std::vector<point<T>>&& pointset) -> rpolygon<T>;

    /**
     * @brief Create a regular object
     *
     * @param pointset
     * @return rpolygon<T>
     */
    static auto create_regular(std::vector<point<T>> pointset) -> rpolygon<T>;

    /**
     * @brief area
     *
     * @return auto
     */
    auto area() const -> T;

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
auto operator<<(Stream& out, const rpolygon<T>& r) -> Stream&
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
void rpolygon<T>::create_ymono_rpolygon(FwIter&& first, FwIter&& last)
{
    auto upward = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) < std::tie(b.y(), b.x());
    };
    auto min_pt = *std::min_element(first, last, upward);
    auto max_pt = *std::max_element(first, last, upward);
    auto dx = max_pt.x() - min_pt.x();
    auto dy = max_pt.y() - min_pt.y();

    FwIter middle;
    if (dx < 0)
    {
        middle = std::partition(first, last, [&](const auto& a) {
            return dx * (a.y() - min_pt.y()) > (a.x() - min_pt.x()) * dy;
        });
    }
    else
    {
        middle = std::partition(first, last, [&](const auto& a) {
            return dx * (a.y() - min_pt.y()) < (a.x() - min_pt.x()) * dy;
        });
    }

    auto downward = [](const auto& a, const auto& b) {
        return std::tie(a.y(), a.x()) > std::tie(b.y(), b.x());
    };
    std::sort(first, middle, upward);
    std::sort(middle, last, downward);
}


/**
 * @brief
 *
 * @tparam T
 * @tparam FwIter
 * @param first
 * @param last
 */
template <typename T>
template <typename FwIter>
void rpolygon<T>::create_test_rpolygon(FwIter&& first, FwIter&& last)
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
auto rpolygon<T>::create_xmonotone(std::vector<point<T>>&& pointset) -> rpolygon<T>
{
    create_xmonotone_i(pointset.begin(), pointset.end());
    return rpolygon<T> {std::forward<std::vector<point<T>>>(pointset)};
}

/**
 * @brief
 *
 * @tparam T
 * @param pointset
 * @return rpolygon<T>
 */
template <typename T>
auto rpolygon<T>::create_ymonotone(std::vector<point<T>>&& pointset) -> rpolygon<T>
{
    using D = std::vector<dualpoint<T>>; // x <-> y
    auto first = reinterpret_cast<D&>(pointset).begin();
    auto last = reinterpret_cast<D&>(pointset).end();
    create_xmonotone_i(std::move(first), std::move(last));
    return rpolygon<T> {std::forward<std::vector<point<T>>>(pointset)};
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
auto rpolygon<T>::area() const -> T
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
