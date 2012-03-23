//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_LENGTH_HPP
#define FAS_TYPE_LIST_LENGTH_HPP

#include <fas/integral/int_.hpp>
#include "detail/length.hpp"

namespace fas{

template<typename L>
struct length
{
  enum { value = detail::length_helper<L>::value  };
  typedef int_<value> type;
};


}

#endif
