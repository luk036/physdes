#include <algorithm>
#include <functional>
#include <recti/rpolygon.hpp>

using namespace recti;

/**
 * @brief 
 * 
 * @tparam T 
 * @param pointset 
 * @return rpolygon<T> 
 */
template <typename T>
rpolygon<T> rpolygon<T>::create_xmonotone(std::vector<point<T>> pointset)
{
    auto first = pointset.begin();
    auto last = pointset.end();
    auto l2r = [](const auto& a, const auto& b) { return a.x() < b.x(); };
    auto r2l = [](const auto& a, const auto& b) { return a.x() > b.x(); };
    auto [min, max] = std::minmax_element(first, last, l2r);
    auto pivot = max->y();

    using Fn = std::function<bool(const point<int>&)>;
    Fn downup = [&pivot](const auto& a) { return a.y() < pivot; };
    Fn updown = [&pivot](const auto& a) { return a.y() > pivot; };
    auto middle =
        std::partition(first, last, (min->y() < pivot) ? downup : updown);
    std::sort(first, middle, std::move(l2r));
    std::sort(middle, last, std::move(r2l));
    return rpolygon<T> {std::move(pointset)};    
}

/**
 * @brief 
 * 
 * @tparam T 
 * @param pointset 
 * @return rpolygon<T> 
 */
template <typename T>
rpolygon<T> rpolygon<T>::create_ymonotone(std::vector<point<T>> pointset)
{
    auto first = pointset.begin();
    auto last = pointset.end();
    auto d2u = [](const auto& a, const auto& b) { return a.y() < b.y(); };
    auto u2d = [](const auto& a, const auto& b) { return a.y() > b.y(); };
    auto [min, max] = std::minmax_element(first, last, d2u);
    auto pivot = max->y();

    using Fn = std::function<bool(const point<int>&)>;
    Fn leftright = [&pivot](const auto& a) { return a.x() < pivot; };
    Fn rightleft = [&pivot](const auto& a) { return a.x() > pivot; };
    auto middle =
        std::partition(first, last, (min->x() < pivot) ? leftright : rightleft);
    std::sort(first, middle, std::move(d2u));
    std::sort(middle, last, std::move(u2d));
    return rpolygon<T> {std::move(pointset)};    
}


namespace recti {

// Instantiation
template class rpolygon<int>;

}