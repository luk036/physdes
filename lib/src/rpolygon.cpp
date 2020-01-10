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
rpolygon<T> rpolygon<T>::create_monotone(std::vector<point<T>> pointset)
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


namespace recti {

// Instantiation
template class rpolygon<int>;

}