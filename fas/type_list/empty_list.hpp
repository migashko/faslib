//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_EMPTY_LIST_HPP
#define FAS_TYPE_LIST_EMPTY_LIST_HPP

#include <fas/type_list/metalist.hpp>

namespace fas{

struct empty_list
{
  typedef metalist::empty_list metatype;
};

}

#endif
