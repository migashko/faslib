//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_TYPE_LIST_REVERSE_HPP
#define FAS_IMPLEMENTATION_TYPE_LIST_REVERSE_HPP

#include "detail/reverse.hpp"

namespace fas{


template<typename T>
struct reverse
{
  typedef typename detail::reverse_helper<T>::type type;
};


}

#endif
