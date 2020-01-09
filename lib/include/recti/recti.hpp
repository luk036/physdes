#ifndef RECTI_HPP
#define RECTI_HPP

#include <tuple>
#include <boost/operators.hpp>

namespace recti
{

/**
 * @brief
 *
 * @tparam T1
 * @tparam T2
 */
template <typename T1, typename T2 = T1>
struct point2D
{
    T1 _x; //!< x coordinate
    T2 _y; //!< y coordinate

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
    bool operator<(const point2D<U1, U2>& rhs) const
    {
        return std::tie(this->_x, this->_y) < std::tie(rhs._x, rhs._y);
    }

    /**
     * @brief
     *
     * @return point2D<T2, T1>
     */
    point2D<T2, T1> flip() const
    {
        return {this->_y, this->_x};
    }
};

template <class Stream, typename T1, typename T2>
Stream& operator<<(Stream& out, const point2D<T1, T2>& p)
{
    out << '(' << p._x / 100.0 << ", " << p._y / 100.0 << ')';
    return out;
}

// template deduction guides (C++17)
template <typename T1, typename T2 = T1> point2D(T1, T2)->point2D<T1, T2>;

/**
 * @brief Interval
 *
 * @tparam T
 */
template <typename T>
struct interval
{
    // requires not(upper < lower)
    T _lower; //> lower bound
    T _upper; //> upper bound

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
        return not(a < this->_lower and this->_upper < a);
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
        return this->_upper < rhs;
    }
};

template <typename T>
bool operator<(const T& lhs, const interval<T>& rhs)
{
    return lhs < rhs._lower;
}


// template deduction guides (C++17)
template <typename T>
interval(T, T)->interval<T>;

/**
 * @brief Rectangle (Rectilinear)
 *
 * @tparam T
 */
template <typename T>
struct rectangle2D : public point2D<interval<T>>
{
    template <typename U>
    bool contains(const point2D<U>& rhs) const
    {
        return this->_x.contains(rhs._x) and this->_y.contains(rhs._y);
    }

    point2D<T> lower() const
    {
        return {this->_x._lower, this->_y._lower};
    }

    point2D<T> upper() const
    {
        return {this->_x._upper, this->_y._upper};
    }
};

template <class Stream, typename T>
Stream& operator<<(Stream& out, const rectangle2D<T>& r)
{
    out << r.lower() << " rectangle " << r.upper();
    return out;
}

// template deduction guides (C++17)
template <typename T>
rectangle2D(interval<T>, interval<T>)->rectangle2D<T>;

/**
 * @brief Horizontal Line Segment
 *
 * @tparam T
 */
template <typename T>
struct hsegment2D : public point2D<interval<T>, T>
{
    template <typename U>
    bool contains(const point2D<U>& rhs) const
    {
        return this->_x.contains(rhs._x) && this->_y == rhs._y;
    }
};

template <typename T>
struct vsegment2D : public point2D<T, interval<T>>
{
    template <typename U>
    bool contains(const point2D<U>& rhs) const
    {
        return this->_y.contains(rhs._y) && this->_x == rhs._x;
    }
};

} // namespace recti
#endif