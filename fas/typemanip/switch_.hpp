//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_SWITCH__HPP
#define FAS_TYPEMANIP_SWITCH__HPP

#include <fas/typemanip/detail/switch_.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/type_list/empty_list.hpp>


namespace fas{

template<
  typename P0 = empty_list, 
  typename P1 = empty_list, 
  typename P2 = empty_list, 
  typename P3 = empty_list, 
  typename P4 = empty_list 
>
struct switch_
{
  typedef typename detail::switch_helper< 
    typename type_list_n<
      P0, P1, P2, P3, P4
    >::type 
  >::type type;
};

}

#endif
