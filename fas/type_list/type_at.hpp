//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_TYPE_AT_HPP
#define FAS_TYPE_LIST_TYPE_AT_HPP

#include <fas/type_list/type_at_c.hpp>

namespace fas{

template<typename I, typename L>
struct type_at
  : type_at_c<I::value, L>
{
};

}

#endif
