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
class rpolygon : public std::vector<point<T> >
{
  private:
    /**
     * @brief Construct a new rpolygon object
     * 
     * @param pointset 
     */
    rpolygon(std::vector<point<T>> pointset)
        : std::vector<point<T> > {std::move(pointset)}
    {
    }

  public:
    /**
     * @brief Create an x-monotone object
     * 
     * @param pointset 
     * @return rpolygon<T> 
     */
    static rpolygon<T> create_xmonotone(std::vector<point<T>> pointset);
    
    /**
     * @brief Create a y-monotone object
     * 
     * @param pointset 
     * @return rpolygon<T> 
     */
    static rpolygon<T> create_ymonotone(std::vector<point<T>> pointset);

    /**
     * @brief
     *
     * @tparam U
     * @param rhs
     * @return true
     * @return false
     */
    template <typename U>
    bool contains(const point<U>& rhs) const;

    /**
     * @brief
     *
     * @return point<T>
     */
    point<T> lower() const;

    /**
     * @brief
     *
     * @return point<T>
     */
    point<T> upper() const;
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
Stream& operator<<(Stream& out, const rpolygon<T>& r)
{
    for (auto&& p : r)
    {
        out << "  \\draw " << p << ";\n";
    }
    return out;
}


} // namespace recti
