#pragma once

#include <boost/operators.hpp>
#include <tuple>
#include <utility> // import std::move

/**
 * @brief vector2
 *
 */
template <typename T = int>
class vector2
    : boost::totally_ordered<vector2<T>,
          boost::additive<vector2<T>, boost::multiplicative<vector2<T>, T>>>
// note: private inheritance is OK here!
{
  private:
    T _x;
    T _y;

  public:
    /**
     * @brief
     *
     */
    constexpr vector2(T&& x, T&& y) noexcept
        : _x {std::move(x)}
        , _y {std::move(y)}
    {
    }

    /**
     * @brief
     *
     */
    constexpr vector2(const T& x, const T& y)
        : _x {x}
        , _y {y}
    {
    }

    /**
     * @brief
     *
     * @return constexpr const T&
     */
    constexpr auto x() const -> const T&
    {
        return this->_x;
    }

    /**
     * @brief
     *
     * @return constexpr const T&
     */
    constexpr auto y() const -> const T&
    {
        return this->_y;
    }

    /**
     * @brief
     *
     * @param rhs
     * @return constexpr vector2&
     */
    constexpr auto operator+=(const vector2& rhs) -> vector2&
    {
        this->_x += rhs.x();
        this->_y += rhs.y();
        return *this;
    }

    /**
     * @brief
     *
     * @param rhs
     * @return constexpr vector2&
     */
    constexpr auto operator-=(const vector2& rhs) -> vector2&
    {
        this->_x -= rhs.x();
        this->_y -= rhs.y();
        return *this;
    }

    /**
     * @brief
     *
     * @param alpha
     * @return constexpr vector2&
     */
    constexpr auto operator*=(const T& alpha) -> vector2&
    {
        this->_x *= alpha;
        this->_y *= alpha;
        return *this;
    }

    /**
     * @brief
     *
     * @param alpha
     * @return constexpr vector2&
     */
    constexpr auto operator/=(const T& alpha) -> vector2&
    {
        this->_x /= alpha;
        this->_y /= alpha;
        return *this;
    }

    /**
     * @brief
     *
     * @param rhs
     * @return true
     * @return false
     */
    constexpr auto operator==(const vector2<T>& rhs) const -> bool
    {
        return std::tie(this->x(), this->y()) == std::tie(rhs.x(), rhs.y());
    }

    /**
     * @brief
     *
     * @param rhs
     * @return true
     * @return false
     */
    constexpr auto operator<(const vector2<T>& rhs) const -> bool
    {
        return std::tie(this->x(), this->y()) < std::tie(rhs.x(), rhs.y());
    }
};


// /**
//  * @brief
//  *
//  * @tparam T
//  * @param lhs
//  * @param rhs
//  * @return constexpr vector2<T>
//  */
// template <class T>
// constexpr vector2<T> operator+(vector2<T> lhs, const vector2<T>& rhs)
// {
//     return lhs += rhs;
// }

// /**
//  * @brief
//  *
//  * @tparam T
//  * @param lhs
//  * @param rhs
//  * @return constexpr vector2<T>
//  */
// template <class T>
// constexpr vector2<T> operator-(vector2<T> lhs, const vector2<T>& rhs)
// {
//     return lhs -= rhs;
// }

// /**
//  * @brief
//  *
//  * @tparam T
//  * @param lhs
//  * @param rhs
//  * @return constexpr vector2<T>
//  */
// template <class T>
// constexpr vector2<T> operator*(vector2<T> lhs, const T& rhs)
// {
//     return lhs *= rhs;
// }

// /**
//  * @brief
//  *
//  * @tparam T
//  * @param lhs
//  * @param rhs
//  * @return constexpr vector2<T>
//  */
// template <class T>
// constexpr vector2<T> operator*(const T& lhs, vector2<T> rhs)
// {
//     return rhs *= lhs;
// }

// /**
//  * @brief
//  *
//  * @tparam T
//  * @param lhs
//  * @param rhs
//  * @return constexpr vector2<T>
//  */
// template <class T>
// constexpr vector2<T> operator/(vector2<T> lhs, const T& rhs)
// {
//     return lhs /= rhs;
// }
