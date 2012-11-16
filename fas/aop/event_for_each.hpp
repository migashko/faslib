//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_EVENT_FOR_EACH_HPP
#define FAS_AOP_EVENT_FOR_EACH_HPP

#include <fas/aop/detail/group_helper.hpp>

namespace fas{

template<typename TgList, typename T, typename F>
inline F event_for_each(T& t, F f)
{
  typedef typename select_event< TgList, T>::type tag_list;
  return detail::group_helper().for_each( tag_list(), t, f);
}

}

#endif
