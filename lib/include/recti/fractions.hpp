// -*- coding: utf-8 -*-
#pragma once

/*! @file include/fractions.hpp
 *  This is a C++ Library header.
 */

#include <cmath>
#include <numeric>
#include <type_traits>
#include <boost/operators.hpp>

namespace fun
{

/*!
 * @brief Greatest common divider
 *
 * @tparam _Mn
 * @param[in] __m
 * @param[in] __n
 * @return _Mn
 */
template <typename _Mn>
constexpr _Mn gcd(_Mn __m, _Mn __n)
{
    return __m == 0 ? abs(__n) : __n == 0 ? abs(__m) : gcd(__n, __m % __n);
}

/*!
 * @brief Least common multiple
 *
 * @tparam _Mn
 * @param[in] __m
 * @param[in] __n
 * @return _Mn
 */
template <typename _Mn>
constexpr _Mn lcm(_Mn __m, _Mn __n)
{
    return (__m != 0 && __n != 0) ? (abs(__m) / gcd(__m, __n)) * abs(__n) : 0;
}

template <typename Z>
struct Fraction
    : boost::totally_ordered<Fraction<Z>
    , boost::totally_ordered<Fraction<Z>, Z
    > >
{
    using _Self = Fraction<Z>;

    Z _numerator;
    Z _denominator;

    /*!
     * @brief Construct a new Fraction object
     *
     * @param[in] numerator
     * @param[in] denominator
     */
    constexpr Fraction(const Z& numerator, const Z& denominator)
    {
        const Z& common = gcd(numerator, denominator);
        _numerator = (common == Z(0)) ? Z(0) : numerator / common;
        _denominator = (common == Z(0)) ? Z(0) : denominator / common;
    }

    /*!
     * @brief Construct a new Fraction object
     *
     * @param[in] numerator
     */
    constexpr explicit Fraction(const Z& numerator)
        : _numerator {numerator}
        , _denominator (1)
    {
    }

    /*!
     * @brief
     *
     * @return const Z&
     */
    constexpr const Z& numerator() const
    {
        return _numerator;
    }

    /*!
     * @brief
     *
     * @return const Z&
     */
    constexpr const Z& denominator() const
    {
        return _denominator;
    }

    /*!
     * @brief
     *
     * @return _Self
     */
    constexpr _Self abs() const
    {
        return _Self(std::abs(_numerator), std::abs(_denominator));
    }

    /*!
     * @brief
     *
     */
    constexpr void reciprocal()
    {
        std::swap(_numerator, _denominator);
    }

    /*!
     * @brief
     *
     * @return _Self
     */
    constexpr _Self operator-() const
    {
        return _Self(-_numerator, _denominator);
    }

    /*!
     * @brief
     *
     * @param[in] frac
     * @return _Self
     */
    constexpr _Self operator+(const _Self& frac) const
    {
        if (_denominator == frac._denominator)
        {
            return _Self(_numerator + frac._numerator, _denominator);
        }
        auto d = _denominator * frac._denominator;
        auto n =
            frac._denominator * _numerator + _denominator * frac._numerator;
        return _Self(n, d);
    }

    /*!
     * @brief
     *
     * @param[in] frac
     * @return _Self
     */
    constexpr _Self operator-(const _Self& frac) const
    {
        return *this + (-frac);
    }

    /*!
     * @brief
     *
     * @param[in] frac
     * @return _Self
     */
    constexpr _Self operator*(const _Self& frac) const
    {
        auto n = _numerator * frac._numerator;
        auto d = _denominator * frac._denominator;
        return _Self(n, d);
    }

    /*!
     * @brief
     *
     * @param[in] frac
     * @return _Self
     */
    constexpr _Self operator/(_Self frac) const
    {
        frac.reciprocal();
        return *this * frac;
    }

    /*!
     * @brief
     *
     * @param[in] i
     * @return _Self
     */
    constexpr _Self operator+(const Z& i) const
    {
        auto n = _numerator + _denominator * i;
        return _Self(n, _denominator);
    }

    /*!
     * @brief
     *
     * @param[in] i
     * @return _Self
     */
    constexpr _Self operator-(const Z& i) const
    {
        return *this + (-i);
    }

    /*!
     * @brief
     *
     * @param[in] i
     * @return _Self
     */
    constexpr _Self operator*(const Z& i) const
    {
        auto n = _numerator * i;
        return _Self(n, _denominator);
    }

    /*!
     * @brief
     *
     * @param[in] i
     * @return _Self
     */
    constexpr _Self operator/(const Z& i) const
    {
        auto d = _denominator * i;
        return _Self(_numerator, d);
    }

    /*!
     * @brief
     *
     * @param[in] frac
     * @return _Self
     */
    constexpr _Self& operator+=(const _Self& frac)
    {
        return *this = *this + frac;
    }

    /*!
     * @brief
     *
     * @param[in] frac
     * @return _Self
     */
    constexpr _Self& operator-=(const _Self& frac)
    {
        return *this = *this - frac;
    }

    /*!
     * @brief
     *
     * @param[in] frac
     * @return _Self
     */
    constexpr _Self& operator*=(const _Self& frac)
    {
        return *this = *this * frac;
    }

    /*!
     * @brief
     *
     * @param[in] frac
     * @return _Self
     */
    constexpr _Self& operator/=(const _Self& frac)
    {
        return *this = *this / frac;
    }

    /*!
     * @brief
     *
     * @param[in] i
     * @return _Self
     */
    constexpr _Self operator+=(const Z& i)
    {
        return *this = *this + i;
    }

    /*!
     * @brief
     *
     * @param[in] i
     * @return _Self
     */
    constexpr _Self operator-=(const Z& i)
    {
        return *this = *this - i;
    }

    /*!
     * @brief
     *
     * @param[in] i
     * @return _Self
     */
    constexpr _Self operator*=(const Z& i)
    {
        return *this = *this * i;
    }

    /*!
     * @brief
     *
     * @param[in] i
     * @return _Self
     */
    constexpr _Self operator/=(const Z& i)
    {
        return *this = *this / i;
    }

    /*!
     * @brief Three way comparison
     *
     * @param[in] frac
     * @return auto
     */
    template <typename U>
    constexpr auto cmp(const Fraction<U>& frac) const
    {
        // if (_denominator == frac._denominator) {
        //     return _numerator - frac._numerator;
        // }
        return _numerator * frac._denominator - _denominator * frac._numerator;
    }

    constexpr bool operator==(const Fraction<Z>& rhs) const
    {
        if (this -> _denominator == rhs._denominator)
        {
            return this->_numerator == rhs._numerator;
        }
        return (this->_numerator * rhs._denominator) ==
            (this->_denominator * rhs._numerator);        
    }

    constexpr bool operator<(const Fraction<Z>& rhs) const
    {
        if (this -> _denominator == rhs._denominator)
        {
            return this->_numerator < rhs._numerator;
        }
        return (this->_numerator * rhs._denominator) <
            (this->_denominator * rhs._numerator);
    }

    /**
     * @brief
     *
     */
    constexpr bool operator==(const Z& rhs) const
    {
        return this->_denominator == Z(1) && this->_numerator == rhs;
    }

    /**
     * @brief
     *
     */
    constexpr bool operator<(const Z& rhs) const
    {
        return this->_numerator < (this->_denominator * rhs);
    }

    /**
     * @brief
     *
     */
    constexpr bool operator>(const Z& rhs) const
    {
        return this->_numerator > (this->_denominator * rhs);
    }

    // /*!
    //  * @brief
    //  *
    //  * @return double
    //  */
    // constexpr explicit operator double()
    // {
    //     return double(_numerator) / _denominator;
    // }

    // /**
    //  * @brief
    //  *
    //  */
    // friend constexpr bool operator<(const Z& lhs, const Fraction<Z>& rhs)
    // {
    //     return lhs * rhs.denominator() < rhs.numerator();
    // }

};


/*!
 * @brief
 *
 * @param[in] c
 * @param[in] frac
 * @return Fraction<Z>
 */
template <typename Z>
constexpr Fraction<Z> operator+(const Z& c, const Fraction<Z>& frac)
{
    return frac + c;
}

/*!
 * @brief
 *
 * @param[in] c
 * @param[in] frac
 * @return Fraction<Z>
 */
template <typename Z>
constexpr Fraction<Z> operator-(const Z& c, const Fraction<Z>& frac)
{
    return c + (-frac);
}

/*!
 * @brief
 *
 * @param[in] c
 * @param[in] frac
 * @return Fraction<Z>
 */
template <typename Z>
constexpr Fraction<Z> operator*(const Z& c, const Fraction<Z>& frac)
{
    return frac * c;
}

/*!
 * @brief
 *
 * @param[in] c
 * @param[in] frac
 * @return Fraction<Z>
 */
template <typename Z>
constexpr Fraction<Z> operator+(int&& c, const Fraction<Z>& frac)
{
    return frac + c;
}

/*!
 * @brief
 *
 * @param[in] c
 * @param[in] frac
 * @return Fraction<Z>
 */
template <typename Z>
constexpr Fraction<Z> operator-(int&& c, const Fraction<Z>& frac)
{
    return (-frac) + c;
}

/*!
 * @brief
 *
 * @param[in] c
 * @param[in] frac
 * @return Fraction<Z>
 */
template <typename Z>
constexpr Fraction<Z> operator*(int&& c, const Fraction<Z>& frac)
{
    return frac * c;
}

/*!
 * @brief
 *
 * @tparam _Stream
 * @tparam Z
 * @param[in] os
 * @param[in] frac
 * @return _Stream&
 */
template <typename _Stream, typename Z>
_Stream& operator<<(_Stream& os, const Fraction<Z>& frac)
{
    os << frac.numerator() << "/" << frac.denominator();
    return os;
}

// For template deduction
// Integral{Z} Fraction(const Z &, const Z &) -> Fraction<Z>;

} // namespace fun
