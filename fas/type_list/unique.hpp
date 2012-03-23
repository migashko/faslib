//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_TYPE_LIST_UNIQUE_HPP
#define FAS_IMPLEMENTATION_TYPE_LIST_UNIQUE_HPP

#include "detail/unique.hpp"

namespace fas{

template<typename L>
struct unique
{
  typedef typename detail::unique_helper<L>::type type;
};

}

#endif
