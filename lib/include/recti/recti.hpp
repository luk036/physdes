#pragma once

// #include <boost/operators.hpp>
#include <cassert>
#include <tuple> // import std::tie()

namespace recti
{

/**
 * @brief 2D point
 *
 * @tparam T1
 * @tparam T2
 */
template <typename T1, typename T2 = T1>
class point
{
  protected:
    T1 _x; //!< x coordinate
    T2 _y; //!< y coordinate

  public:
    /**
     * @brief Construct a new point object
     *
     * @param x
     * @param y
     */
    constexpr point(T1 x, T2 y)
        : _x {std::move(x)}
        , _y {std::move(y)}
    {
    }

    /**
     * @brief
     *
     * @return const T1&
     */
    constexpr const T1& x() const
    {
        return this->_x;
    }

    /**
     * @brief
     *
     * @return T1&
     */
    constexpr T1& x()
    {
        return this->_x;
    }

    /**
     * @brief
     *
     * @return const T2&
     */
    constexpr const T2& y() const
    {
        return this->_y;
    }

    /**
     * @brief
     *
     * @return T2&
     */
    constexpr T2& y()
    {
        return this->_y;
    }

    /**
     * @brief
     *
     * @tparam U1
     * @tparam U2
     * @param rhs
     * @return true
     * @return false
     */
    // template <typename U1, typename U2>
    // bool operator<(const point<U1, U2>& rhs) const
    // {
    //     return std::tie(this->x(), this->y()) < std::tie(rhs.x(), rhs.y());
    // }

    constexpr auto operator<=>(const point<T1, T2>& rhs) const = default;

    /**
     * @brief
     *
     * @return point<T2, T1>
     */
    constexpr point<T2, T1> flip() const
    {
        return {this->y(), this->x()};
    }
};

/**
 * @brief 2D point
 *
 * @tparam T1
 * @tparam T2
 */
template <typename T1, typename T2 = T1>
class dualpoint : public point<T1, T2>
{
  public:
    /**
     * @brief
     *
     * @return const T1&
     */
    constexpr const T1& y() const // override intentionally
    {
        return this->_x;
    }

    /**
     * @brief
     *
     * @return T1&
     */
    constexpr T1& y() // override intentionally
    {
        return this->_x;
    }

    /**
     * @brief
     *
     * @return const T2&
     */
    constexpr const T2& x() const // override intentionally
    {
        return this->_y;
    }

    /**
     * @brief
     *
     * @return T2&
     */
    constexpr T2& x() // override intentionally
    {
        return this->_y;
    }

    /**
     * @brief ???
     *
     */
    constexpr auto operator<=>(const dualpoint<T1, T2>& rhs) const = default;
};


/**
 * @brief
 *
 * @tparam Stream
 * @tparam T1
 * @tparam T2
 * @param out
 * @param p
 * @return Stream&
 */
template <class Stream, typename T1, typename T2>
Stream& operator<<(Stream& out, const point<T1, T2>& p)
{
    out << '(' << p.x() / 100.0 << ", " << p.y() / 100.0 << ')';
    return out;
}


/**
 * @brief Interval
 *
 * @tparam T
 */
template <typename T>
class interval
{
  private:
    T _lower; //> lower bound
    T _upper; //> upper bound

  public:
    /**
     * @brief Construct a new interval object
     *
     * @param lower
     * @param upper
     */
    constexpr interval(T lower, T upper)
        : _lower {std::move(lower)}
        , _upper {std::move(upper)}
    {
        assert(!(_upper < _lower));
    }

    /**
     * @brief
     *
     * @return const T&
     */
    constexpr const T& lower() const
    {
        return this->_lower;
    }

    /**
     * @brief
     *
     * @return T&
     */
    constexpr T& lower()
    {
        return this->_lower;
    }

    /**
     * @brief
     *
     * @return const T&
     */
    constexpr const T& upper() const
    {
        return this->_upper;
    }

    /**
     * @brief
     *
     * @return T&
     */
    constexpr T& upper()
    {
        return this->_upper;
    }

    /**
     * @brief
     *
     * @return auto
     */
    constexpr T len() const
    {
        return this->upper() - this->lower();
    }

    /**
     * @brief
     *
     * @param rhs
     * @return true
     * @return false
     */
    constexpr bool operator==(const interval<T>& rhs) const = default;

    // auto operator<=>(const interval<T>& rhs) const = default;

    template <typename U>
    constexpr std::partial_ordering operator<=>(const interval<U>& rhs) const
    {
        if (this->upper() == rhs.upper() && this->lower() == rhs.lower())
        {
            return std::partial_ordering::equivalent;
        }
        if (this->upper() < rhs.lower())
        {
            return std::partial_ordering::less;
        }
        if (this->lower() > rhs.upper())
        {
            return std::partial_ordering::greater;
        }
        return std::partial_ordering::unordered;
        // return std::partial_ordering::equivalent;
    }

    template <typename U>
    constexpr bool contains(const interval<U>& a) const
    {
        return !(a.lower() < this->lower() || this->upper() < a.upper());
    }

    /**
     * @brief
     *
     * @param x
     * @return true
     * @return false
     */
    constexpr bool contains(const T& a) const
    {
        return !(a < this->lower() || this->upper() < a);
    }

    /**
     * @brief
     *
     * @param rhs
     * @return true
     * @return false
     */
    constexpr bool operator<(const T& rhs) const
    {
        return this->upper() < rhs;
    }
};

/**
 * @brief
 *
 * @tparam T
 * @param lhs
 * @param rhs
 * @return true
 * @return false
 */
template <typename T>
constexpr bool operator<(const T& lhs, const interval<T>& rhs)
{
    return lhs < rhs.lower();
}


/**
 * @brief Rectangle (Rectilinear)
 *
 * @tparam T
 */
template <typename T>
struct rectangle : point<interval<T>>
{
    /**
     * @brief Construct a new rectangle object
     *
     * @param x
     * @param y
     */
    constexpr rectangle(interval<T> x, interval<T> y)
        : point<interval<T>> {std::move(x), std::move(y)}
    {
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
    constexpr bool contains(const point<U>& rhs) const
    {
        return this->x().contains(rhs.x()) && this->y().contains(rhs.y());
    }

    /**
     * @brief
     *
     * @return point<T>
     */
    constexpr point<T> lower() const
    {
        return {this->x().lower(), this->y().lower()};
    }

    /**
     * @brief
     *
     * @return point<T>
     */
    constexpr point<T> upper() const
    {
        return {this->x().upper(), this->y().upper()};
    }

    constexpr T area() const
    {
        return this->x().len() * this->y().len();
    }
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
Stream& operator<<(Stream& out, const rectangle<T>& r)
{
    out << r.lower() << " rectangle " << r.upper();
    return out;
}


/**
 * @brief Horizontal Line Segment
 *
 * @tparam T
 */
template <typename T>
struct hsegment : point<interval<T>, T>
{
    /**
     * @brief Construct a new hsegment object
     *
     * @param x
     * @param y
     */
    constexpr hsegment(interval<T> x, T y)
        : point<interval<T>, T> {std::move(x), std::move(y)}
    {
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
    constexpr bool contains(const point<U>& rhs) const
    {
        return this->y() == rhs.y() && this->x().contains(rhs.x());
    }
};

template <typename T>
struct vsegment : point<T, interval<T>>
{
    /**
     * @brief Construct a new vsegment object
     *
     * @param x
     * @param y
     */
    constexpr vsegment(T x, interval<T> y)
        : point<T, interval<T>> {std::move(x), std::move(y)}
    {
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
    constexpr bool contains(const point<U>& rhs) const
    {
        return this->x() == rhs.x() && this->y().contains(rhs.y());
    }
};

} // namespace recti
