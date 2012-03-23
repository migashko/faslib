//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_TYPE_LIST_TYPE_AT_C_HPP
#define FAS_IMPLEMENTATION_TYPE_LIST_TYPE_AT_C_HPP

#include "detail/type_at.hpp"

namespace fas{

template<int I, typename L>
struct type_at_c
{
  typedef detail::type_at_helper<I, L> helper;
public:
  typedef typename helper::type type;
  typedef typename helper::tail tail;
  typedef typename helper::fulltail fulltail;
};


}

#endif
