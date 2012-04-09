#ifndef FAS_RANGE_END_HPP
#define FAS_RANGE_END_HPP

#include <fas/range/typerange.hpp>
#include <cstddef>

namespace fas{

template<typename T>
inline typename typerange<T>::iterator end(T& t)
{
  return typerange<T>::end(t);
}

}

#endif
