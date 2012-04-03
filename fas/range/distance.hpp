#ifndef FAS_RANGE_DISTANCE_HPP
#define FAS_RANGE_DISTANCE_HPP

#include <fas/range/typerange.hpp>
#include <cstddef>


namespace fas{


  /*
template<typename P>
inline std::ptrdiff_t distance(P* t)
{
  return 0;
}

template<typename P>
inline std::ptrdiff_t distance(const P* t)
{
  return 0;
}

*/
template<typename C>
inline typename typerange<const C>::difference_type distance(const C& t)
{
  return typerange<const C>::distance(t)/*std::distance( t.begin(), t.end() )*/;
}


}

#endif
