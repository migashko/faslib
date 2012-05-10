//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_TYPE_LIST_HPP
#define FAS_TYPE_LIST_TYPE_LIST_HPP

#include <fas/type_list/metalist.hpp>
#include <fas/type_list/empty_list.hpp>

namespace fas{

template< typename L, typename R = empty_list >
struct type_list
{
  typedef ::fas::metalist::type_list metatype;
  typedef L left_type;
  typedef R right_type;
};

  
}

#endif
