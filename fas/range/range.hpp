#ifndef FAS_RANGE_RANGE_HPP
#define FAS_RANGE_RANGE_HPP

#include <fas/range/typerange.hpp>
#include <fas/range/string_range.hpp>

namespace fas{

template<typename I>
inline typename typerange<I>::range range(I beg, I end)
{
  return typerange<I>::make_range(beg, end);
}

// ic iterator, container or array

template<typename IC>
inline typename typerange<const IC>::range range(const IC& cnt)
{
  return typerange<const IC>::make_range(cnt);
}


template<typename IC>
inline typename typerange<IC>::range range(IC& cnt)
{
  return typerange<IC>::make_range(cnt);
}

template<typename IC>
inline typename typerange<IC>::range end_range(IC& cnt)
{
  return typerange<IC>::make_end_range(cnt);
}



template<typename C>
inline typename typerange<C>::init_range init_range(C& cnt, bool clear = false)
{
  return typerange<C>::make_init_range(cnt, clear);
}

template<typename C>
inline string_range<C*> srange(C* str)
{
  return string_range<C*>(str);
}



}

#endif
