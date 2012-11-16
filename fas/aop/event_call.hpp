//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_EVENT_CALL_HPP
#define FAS_AOP_EVENT_CALL_HPP

#include <fas/aop/detail/group_helper.hpp>
#include <fas/aop/select_event.hpp>

namespace fas{

template<typename TgList, typename T>
inline void event_call(T& t)
{
  typedef typename select_event< TgList, T>::type tag_list;
  detail::group_helper().call( tag_list(), t);
}

template<typename TgList, typename T, typename P1>
inline void event_call(T& t, P1 p1)
{
  typedef typename select_event< TgList, T>::type tag_list;
  detail::group_helper().call( tag_list(), t, p1);
}

template<typename TgList, typename T, typename P1, typename P2>
inline void event_call(T& t, P1 p1, P2 p2)
{
  typedef typename select_event< TgList, T>::type tag_list;
  detail::group_helper().call( tag_list(), t, p1, p2);
}

template<typename TgList, typename T, typename P1, typename P2, typename P3>
inline void event_call(T& t, P1 p1, P2 p2, P3 p3)
{
  typedef typename select_event< TgList, T>::type tag_list;
  detail::group_helper().call( tag_list(), t, p1, p2, p3);
}

template<typename TgList, typename T, typename P1, typename P2, typename P3, typename P4>
inline void event_call(T& t, P1 p1, P2 p2, P3 p3, P4 p4)
{
  typedef typename select_event< TgList, T>::type tag_list;
  detail::group_helper().call( tag_list(),t, p1, p2, p3, p4);
}

template<typename TgList, typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
inline void event_call(T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
{
  typedef typename select_event< TgList, T>::type tag_list;
  detail::group_helper().call( tag_list(), t, p1, p2, p3, p4, p5);
}

}

#endif
