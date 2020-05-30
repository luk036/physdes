#pragma once

/**
 * @brief vector2
 *
 */
template <class T>
class vector2                      // note: private inheritance is OK here!
{
  private:
    T _x;
    T _y;

  public:
    constexpr vector2(T x, T y) : _x{std::move(x)}, _y{std::move(y)} {}

    constexpr const T& x() const { return this->_x; }
    constexpr const T& y() const { return this->_y; }

    constexpr vector2& operator+=(const vector2& rhs)
    {
        this->_x += rhs.x();
        this->_y += rhs.y();
        return *this;
    }

    constexpr vector2& operator-=(const vector2& rhs)
    {
        this->_x -= rhs.x();
        this->_y -= rhs.y();
        return *this;
    }

    constexpr vector2& operator*=(const T& alpha)
    {
        this->_x *= alpha;
        this->_y *= alpha;
        return *this;
    }

    constexpr vector2& operator/=(const T& alpha)
    {
        this->_x /= alpha;
        this->_y /= alpha;
        return *this;
    }

    constexpr bool operator==(const vector2<T>& rhs) const
    {
        return this->_x == rhs._x && this->_y == rhs._y;
    }

    constexpr bool operator!=(const vector2<T>& rhs) const
    {
        return !(*this == rhs);
    }
};


template <class T>
constexpr vector2<T> operator+(vector2<T> lhs, const vector2<T>& rhs)
{
    return lhs += rhs;
}

template <class T>
constexpr vector2<T> operator-(vector2<T> lhs, const vector2<T>& rhs)
{
    return lhs -= rhs;
}

template <class T>
constexpr vector2<T> operator*(vector2<T> lhs, const T& rhs)
{
    return lhs *= rhs;
}

template <class T>
constexpr vector2<T> operator*(const T& lhs, vector2<T> rhs)
{
    return rhs *= lhs;
}

template <class T>
constexpr vector2<T> operator/(vector2<T> lhs, const T& rhs)
{
    return lhs /= rhs;
}
