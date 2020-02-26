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
    point(T1 x, T2 y)
        : _x {std::move(x)}
        , _y {std::move(y)}
    {
    }

    /**
     * @brief
     *
     * @return const T1&
     */
    const T1& x() const
    {
        return this->_x;
    }

    /**
     * @brief
     *
     * @return T1&
     */
    T1& x()
    {
        return this->_x;
    }

    /**
     * @brief
     *
     * @return const T2&
     */
    const T2& y() const
    {
        return this->_y;
    }

    /**
     * @brief
     *
     * @return T2&
     */
    T2& y()
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
    template <typename U1, typename U2>
    bool operator<(const point<U1, U2>& rhs) const
    {
        return std::tie(this->x(), this->y()) < std::tie(rhs.x(), rhs.y());
    }

    /**
     * @brief
     *
     * @return point<T2, T1>
     */
    point<T2, T1> flip() const
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
    const T1& y() const // override intentionally
    {
        return this->_x;
    }

    /**
     * @brief
     *
     * @return T1&
     */
    T1& y() // override intentionally
    {
        return this->_x;
    }

    /**
     * @brief
     *
     * @return const T2&
     */
    const T2& x() const // override intentionally
    {
        return this->_y;
    }

    /**
     * @brief
     *
     * @return T2&
     */
    T2& x() // override intentionally
    {
        return this->_y;
    }
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
    interval(T lower, T upper)
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
    const T& lower() const
    {
        return this->_lower;
    }

    /**
     * @brief
     *
     * @return T&
     */
    T& lower()
    {
        return this->_lower;
    }

    /**
     * @brief
     *
     * @return const T&
     */
    const T& upper() const
    {
        return this->_upper;
    }

    /**
     * @brief
     *
     * @return T&
     */
    T& upper()
    {
        return this->_upper;
    }

    /**
     * @brief
     *
     * @return auto
     */
    T len() const
    {
        return this->upper() - this->lower();
    }

    /**
     * @brief
     *
     * @param x
     * @return true
     * @return false
     */
    template <typename U>
    bool contains(const U& a) const
    {
        return !(a < this->lower() && this->upper() < a);
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
    bool operator<(const U& rhs) const
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
bool operator<(const T& lhs, const interval<T>& rhs)
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
    rectangle(interval<T> x, interval<T> y)
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
    bool contains(const point<U>& rhs) const
    {
        return this->x().contains(rhs.x()) && this->y().contains(rhs.y());
    }

    /**
     * @brief
     *
     * @return point<T>
     */
    point<T> lower() const
    {
        return {this->x().lower(), this->y().lower()};
    }

    /**
     * @brief
     *
     * @return point<T>
     */
    point<T> upper() const
    {
        return {this->x().upper(), this->y().upper()};
    }

    T area() const
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
    hsegment(interval<T> x, T y)
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
    bool contains(const point<U>& rhs) const
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
    vsegment(T x, interval<T> y)
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
    bool contains(const point<U>& rhs) const
    {
        return this->x() == rhs.x() && this->y().contains(rhs.y());
    }
};

} // namespace recti
