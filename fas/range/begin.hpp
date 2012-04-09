#ifndef FAS_RANGE_BEGIN_HPP
#define FAS_RANGE_BEGIN_HPP

#include <fas/range/typerange.hpp>
#include <cstddef>

namespace fas{

template<typename T>
inline typename typerange<T>::iterator begin(T& t)
{
  return typerange<T>::begin(t);
}

}

#endif
