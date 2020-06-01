#pragma once

#include <utility> // import std::move

/**
 * @brief vector2
 *
 */
template <typename T=int>
class vector2 // note: private inheritance is OK here!
{
  private:
    T _x;
    T _y;

  public:
    /**
     * @brief 
     * 
     */
    constexpr vector2(T x, T y)
        : _x {std::move(x)}
        , _y {std::move(y)}
    {
    }

    /**
     * @brief 
     * 
     * @return constexpr const T& 
     */
    constexpr const T& x() const
    {
        return this->_x;
    }

    /**
     * @brief 
     * 
     * @return constexpr const T& 
     */
    constexpr const T& y() const
    {
        return this->_y;
    }

    /**
     * @brief 
     * 
     * @param rhs 
     * @return constexpr vector2& 
     */
    constexpr vector2& operator+=(const vector2& rhs)
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
    constexpr vector2& operator-=(const vector2& rhs)
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
    constexpr vector2& operator*=(const T& alpha)
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
    constexpr vector2& operator/=(const T& alpha)
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
    constexpr bool operator==(const vector2<T>& rhs) const
    {
        return this->_x == rhs._x && this->_y == rhs._y;
    }

    /**
     * @brief 
     * 
     * @param rhs 
     * @return true 
     * @return false 
     */
    constexpr bool operator!=(const vector2<T>& rhs) const
    {
        return !(*this == rhs);
    }
};


/**
 * @brief 
 * 
 * @tparam T 
 * @param lhs 
 * @param rhs 
 * @return constexpr vector2<T> 
 */
template <class T>
constexpr vector2<T> operator+(vector2<T> lhs, const vector2<T>& rhs)
{
    return lhs += rhs;
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param lhs 
 * @param rhs 
 * @return constexpr vector2<T> 
 */
template <class T>
constexpr vector2<T> operator-(vector2<T> lhs, const vector2<T>& rhs)
{
    return lhs -= rhs;
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param lhs 
 * @param rhs 
 * @return constexpr vector2<T> 
 */
template <class T>
constexpr vector2<T> operator*(vector2<T> lhs, const T& rhs)
{
    return lhs *= rhs;
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param lhs 
 * @param rhs 
 * @return constexpr vector2<T> 
 */
template <class T>
constexpr vector2<T> operator*(const T& lhs, vector2<T> rhs)
{
    return rhs *= lhs;
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param lhs 
 * @param rhs 
 * @return constexpr vector2<T> 
 */
template <class T>
constexpr vector2<T> operator/(vector2<T> lhs, const T& rhs)
{
    return lhs /= rhs;
}
