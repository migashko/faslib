//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_GROUP_CALL_HPP
#define FAS_AOP_GROUP_CALL_HPP

#include <fas/type_list/head.hpp>
#include <fas/type_list/tail.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/normalize.hpp>

#include <fas/typemanip/if_c.hpp>
#include <fas/typemanip/some_type.hpp>
#include <fas/typemanip/empty_type.hpp>
/*
#include <fas/aop/metalist.hpp>
#include <fas/type_list/normalize.hpp>
*/

namespace fas{

namespace detail{

// строит из смешенного списка тегов (групп и обячных адвайсов),
// один плоский спискок, куда включенны адвайсы всех групп
template< typename TgList, typename A >
struct group_tags_getter
{
  typedef typename head<TgList>::type head;
  typedef typename tail<TgList>::type tail;
  typedef type_list< head, tail> tag_list;
  typedef typename group_tags_getter< tag_list, A >::type type;
};

template< typename L, typename R, typename A >
struct group_tags_getter< fas::type_list<L, R>, A >
{
  typedef typename A::template select_group<L>::type group_tags;
  
  typedef typename fas::if_c<
    fas::some_type<group_tags, fas::empty_type>::value,
    L,
    group_tags
  >::type current_tags;
  
  typedef typename fas::merge<
    current_tags,
    typename group_tags_getter< R, A >::type
  >::type type;
};

template< typename A >
struct group_tags_getter< fas::empty_list, A >
{
  typedef fas::empty_list type;
};

/// 0
template<typename TgList, typename A, typename T>
inline void group_call_helper( TgList, A& a, T& t)
{
  a.template get< typename fas::head<TgList>::type >()(t);
  group_call_helper( typename fas::tail<TgList>::type(), a, t);
}

template<typename A, typename T>
inline void group_call_helper( fas::empty_list, A& , T& ) { }

/// 1
template<typename TgList, typename A, typename T, typename P1>
inline void group_call_helper( TgList, A& a, T& t, P1 p1)
{
  a.template get< typename fas::head<TgList>::type >()(t, p1);
  group_call_helper( typename fas::tail<TgList>::type(), a, t, p1);
}

template<typename A, typename T, typename P1>
inline void group_call_helper( fas::empty_list, A& , T&, P1 ) { }

/// 2
template<typename TgList, typename A, typename T, typename P1, typename P2>
inline void group_call_helper( TgList, A& a, T& t, P1 p1, P2 p2)
{
  a.template get< typename fas::head<TgList>::type >()(t, p1, p2);
  group_call_helper( typename fas::tail<TgList>::type(), a, t, p1, p2);
}

template<typename A, typename T, typename P1, typename P2>
inline void group_call_helper( fas::empty_list, A&, T&, P1, P2 ) { }

/// 3
template<typename TgList, typename A, typename T, typename P1, typename P2, typename P3>
inline void group_call_helper( TgList, A& a, T& t, P1 p1, P2 p2, P3 p3)
{
  a.template get< typename fas::head<TgList>::type >()(t, p1, p2, p3);
  group_call_helper( typename fas::tail<TgList>::type(), a, t, p1, p2, p3);
}

template<typename A, typename T, typename P1, typename P2, typename P3>
inline void group_call_helper( fas::empty_list, A&, T&, P1, P2, P3 ) { }

/// 4
template<typename TgList, typename A, typename T, typename P1, typename P2, typename P3, typename P4>
inline void group_call_helper( TgList, A& a, T& t, P1 p1, P2 p2, P3 p3, P4 p4)
{
  a.template get< typename fas::head<TgList>::type >()(t, p1, p2, p3, p4);
  group_call_helper( typename fas::tail<TgList>::type(), a, t, p1, p2, p3, p4);
}

template<typename A, typename T, typename P1, typename P2, typename P3, typename P4>
inline void group_call_helper( fas::empty_list, A&, T&, P1, P2, P3, P4 ) { }

/// 5
template<typename TgList, typename A, typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
inline void group_call_helper( TgList, A& a, T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
{
  a.template get< typename fas::head<TgList>::type >()(t, p1, p2, p3, p4, p5);
  group_call_helper( typename fas::tail<TgList>::type(), a, t, p1, p2, p3, p4, p5);
}

template<typename A, typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
inline void group_call_helper( fas::empty_list, A&, T&, P1, P2, P3, P4, P5) { }


} // detail


template<typename TgList, typename A, typename T>
inline void group_call(A& a, T& t)
{
  typedef typename detail::group_tags_getter< typename fas::normalize<TgList>::type, A>::type tag_list;
  group_call_helper( tag_list(), a, t);
}


}

#endif
