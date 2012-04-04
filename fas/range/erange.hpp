#ifndef FAS_RANGE_ERANGE_HPP
#define FAS_RANGE_ERANGE_HPP

#include <fas/range/typerange.hpp>
#include <fas/range/string_range.hpp>

namespace fas{

template<typename IC>
inline typename typerange<IC>::range erange(IC& cnt)
{
  return typerange<IC>::make_erange(cnt);
}

}

#endif
