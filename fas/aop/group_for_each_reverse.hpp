//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_GROUP_FOR_EACH_REVERSE_HPP
#define FAS_AOP_GROUP_FOR_EACH_REVERSE_HPP

#include <fas/aop/detail/group_helper.hpp>
#include <fas/aop/select_group.hpp>
#include <fas/type_list/reverse.hpp>

namespace fas{

template<typename TgList, typename T, typename F>
inline F group_for_each_reverse(T& t, F f)
{
  typedef typename select_group< TgList, T>::type tag_list;
  return detail::group_helper().for_each( typename reverse<tag_list>::type(), t, f);
}

}

#endif
