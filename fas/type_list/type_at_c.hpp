//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_TYPE_AT_C_HPP
#define FAS_TYPE_LIST_TYPE_AT_C_HPP

#include <fas/type_list/detail/type_at.hpp>

namespace fas{

template<int I, typename L>
struct type_at_c
{
  typedef detail::type_at_impl<I, L> helper;
public:
  typedef typename helper::type type;
  typedef typename helper::tail tail;
  typedef typename helper::fulltail fulltail;
};

}

#endif
