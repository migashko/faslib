//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_BIND_HPP
#define FAS_MP_BIND_HPP

#include <fas/mp/detail/bind.hpp>
#include <fas/type_list/empty_list.hpp>


namespace fas{

template<typename PE, typename L = empty_list >
struct bind
{
  typedef typename detail::bind_helper<PE, L >::type type;
};
 
}

#endif

