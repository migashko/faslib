#ifndef FAS_RANGE_DISTANCE_HPP
#define FAS_RANGE_DISTANCE_HPP


#include <fas/range/range_traits.hpp>

namespace fas{

template<typename P>
typename typerange<P*>::difference_type distance(P* t)
{
  return 0;
}

template<typename C>
typename typerange<C>::difference_type distance(const C& t)
{
  return std::distance( t.begin(), t.end() );
}


}

#endif
