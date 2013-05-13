//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_SELECT_GROUP_REVERSE_HPP
#define FAS_AOP_SELECT_GROUP_REVERSE_HPP

#include <fas/aop/detail/select_group.hpp>
#include <fas/type_list/reverse.hpp>

namespace fas{


template< typename TgList, typename T >
struct select_group_reverse
{
  typedef typename reverse<
    typename detail::select_group_aspect<TgList, typename T::aspect>::type
  >::type type;
};


}

#endif
