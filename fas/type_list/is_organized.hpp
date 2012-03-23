//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_IS_ORGANIZED_HPP
#define FAS_TYPE_LIST_IS_ORGANIZED_HPP

#include "detail/is_organized.hpp"
#include <fas/integral/bool_.hpp>

namespace fas{

template<typename L>
struct is_organized
{
  enum { value = detail::is_organized_helper<L>::value};
  typedef bool_<value> type;
};


}


#endif
