//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_SELECT_GROUP_HPP
#define FAS_AOP_SELECT_GROUP_HPP

#include <fas/aop/detail/select_group.hpp>

namespace fas{

template< typename TgList, typename T >
struct select_group
{
  typedef typename detail::select_group<TgList, typename T::aspect>::type type;
};

}

#endif
