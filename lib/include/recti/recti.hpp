#ifndef RECTI_HPP
#define RECTI_HPP

// #include <boost/operators.hpp>
#include <cassert>
#include <tuple>

/**
 * @brief
 *
 * @todo rpolygon
 *
 */
namespace recti
{

/**
 * @brief
 *
 * @tparam T1
 * @tparam T2
 */
template <typename T1, typename T2 = T1>
class point
{
  private:
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

    const T1& x() const
    {
        return this->_x;
    }

    T1& x()
    {
        return this->_x;
    }

    const T2& y() const
    {
        return this->_y;
    }

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

template <class Stream, typename T1, typename T2>
Stream& operator<<(Stream& out, const point<T1, T2>& p)
{
    out << '(' << p.x() / 100.0 << ", " << p.y() / 100.0 << ')';
    return out;
}

// template deduction guides (C++17)
// template <typename T1, typename T2 = T1>
// point(T1, T2)->point<T1, T2>;

/**
 * @brief Interval
 *
 * @tparam T
 */
template <typename T>
class interval
{
  private:
    // requires not(upper < lower)
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
        assert(not(_upper < _lower));
    }

    const T& lower() const
    {
        return this->_lower;
    }

    T& lower()
    {
        return this->_lower;
    }

    const T& upper() const
    {
        return this->_upper;
    }

    T& upper()
    {
        return this->_upper;
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
        return not(a < this->lower() and this->upper() < a);
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

template <typename T>
bool operator<(const T& lhs, const interval<T>& rhs)
{
    return lhs < rhs.lower();
}


// template deduction guides (C++17)
// template <typename T>
// interval(T, T)->interval<T>;

/**
 * @brief Rectangle (Rectilinear)
 *
 * @tparam T
 */
template <typename T>
class rectangle : public point<interval<T>>
{
  public:
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

    template <typename U>
    bool contains(const point<U>& rhs) const
    {
        return this->x().contains(rhs.x()) and this->y().contains(rhs.y());
    }

    point<T> lower() const
    {
        return {this->x().lower(), this->y().lower()};
    }

    point<T> upper() const
    {
        return {this->x().upper(), this->y().upper()};
    }
};

template <class Stream, typename T>
Stream& operator<<(Stream& out, const rectangle<T>& r)
{
    out << r.lower() << " rectangle " << r.upper();
    return out;
}

// template deduction guides (C++17)
// template <typename T>
// rectangle(interval<T>, interval<T>)->rectangle<T>;

/**
 * @brief Horizontal Line Segment
 *
 * @tparam T
 */
template <typename T>
struct hsegment : public point<interval<T>, T>
{
    template <typename U>
    bool contains(const point<U>& rhs) const
    {
        return this->x().contains(rhs.x()) && this->y() == rhs.y();
    }
};

template <typename T>
struct vsegment : public point<T, interval<T>>
{
    template <typename U>
    bool contains(const point<U>& rhs) const
    {
        return this->y().contains(rhs.y()) && this->x() == rhs.x();
    }
};

} // namespace recti
#endif