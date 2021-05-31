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
        assert(n >= 2);
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
    assert(first != last);

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
    assert(first != last);

    const auto leftmost = *std::min_element(first, last);
    const auto rightmost = *std::max_element(first, last);
    const auto d = rightmost - leftmost;
    auto r2l = [&](const auto& a) { return d.cross(a - leftmost) <= 0; };
    const auto middle = std::partition(first, last, std::move(r2l));
    std::sort(first, middle);
    std::sort(middle, last, std::greater<>());
}


template <typename T>
inline bool point_in_polygon(const std::vector<point<T>>& S, point<T>&& q)
{
    auto c = false;
    auto p0 = S.back();
    for (auto&& p1 : S)
    {
        if ((p1.y() <= q.y() && q.y() < p0.y()) ||
            (p0.y() <= q.y() && q.y() < p1.y()))
        {
            auto d = (q - p0).cross(p1 - p0);
            if (p1.y() > p0.y())
            {
                if (d < 0)
                {
                    c = !c;
                }
            }
            else
            { // v1.y() < v0.y()
                if (d > 0)
                {
                    c = !c;
                }
            }
        }
        p0 = p1;
    }
    return c;
}


} // namespace recti
