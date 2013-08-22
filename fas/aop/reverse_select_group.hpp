//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_REVERSE_SELECT_GROUP_HPP
#define FAS_AOP_REVERSE_SELECT_GROUP_HPP

#include <fas/aop/detail/select_group.hpp>
#include <fas/type_list/reverse.hpp>

namespace fas{

template< typename TgList, typename T >
struct reverse_select_group
{
  typedef typename reverse<
    typename detail::select_group<TgList, typename T::aspect>::type
  >::type type;
};


}

#endif
