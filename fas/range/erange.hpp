//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_ERANGE_HPP
#define FAS_RANGE_ERANGE_HPP

#include <fas/range/typerange.hpp>

namespace fas{

template<typename IC>
inline typename typerange<IC>::range erange(IC& cnt)
{
  return typerange<IC>::make_erange(cnt);
}

}

#endif
