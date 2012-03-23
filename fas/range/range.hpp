#ifndef FAS_RANGE_RANGE_HPP
#define FAS_RANGE_RANGE_HPP

#include <fas/range/range_traits.hpp>
#include <fas/range/string_range.hpp>

namespace fas{

template<typename I>
inline typename range_traits<I>::range range(I beg, I end)
{
  return range_traits<I>::make_range(beg, end);
}

// ic iterator, container or array

template<typename IC>
inline typename range_traits<const IC>::range range(const IC& cnt)
{
  return range_traits<const IC>::make_range(cnt);
}


template<typename IC>
inline typename range_traits<IC>::range range(IC& cnt)
{
  return range_traits<IC>::make_range(cnt);
}

template<typename IC>
inline typename range_traits<IC>::range end_range(IC& cnt)
{
  return range_traits<IC>::make_end_range(cnt);
}



template<typename C>
inline typename range_traits<C>::init_range init_range(C& cnt, bool clear = false)
{
  return range_traits<C>::make_init_range(cnt, clear);
}

template<typename C>
inline string_range<C*> srange(C* str)
{
  return string_range<C*>(str);
}



}

#endif
