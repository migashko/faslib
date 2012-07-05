//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_GROUP_CALL_HPP
#define FAS_AOP_DETAIL_GROUP_CALL_HPP

#include <fas/aop/tag.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/integral/int_.hpp>

namespace fas { namespace detail {

struct group_helper
{

template<typename L, typename T, typename F, int N >
static inline F for_each_group(L, T&, F f, int_<N>, int_<N>) 
{
  return f; 
}

template<typename L, typename T, typename F, int C, int N  >
static inline F for_each_group(L, T& t, F f, int_<C>, int_<N> )
{
  typedef typename type_at_c< C, L>::type head;
  f(t, tag<head>() );
  return for_each_group( L(), t, f, int_<C+1>(), int_<N>() );
}

/// 0
template<typename T >
static inline void group_call_helper(empty_list, T&) 
{
}

template<typename L, typename R, typename T >
static inline void group_call_helper(type_list<L, R>, T& t )
{
  t.get_aspect().template get<L>()(t);
  group_call_helper( R(), t);
}

/// 1
template<typename T, typename P1 >
static inline void group_call_helper(empty_list, T&, P1)
{
}

template<typename L, typename R, typename T, typename P1 >
static inline void group_call_helper(type_list<L, R>, T& t, P1 p1)
{
  t.get_aspect().template get<L>()(t, p1);
  group_call_helper( R(), t, p1);
}

/// 2
template<typename T, typename P1, typename P2 >
static inline void group_call_helper(empty_list, T&, P1, P2) 
{
}

template<typename L, typename R, typename T, typename P1, typename P2 >
static inline void group_call_helper(type_list<L, R>, T& t, P1 p1, P2 p2)
{
  t.get_aspect().template get<L>()(t, p1, p2);
  group_call_helper( R(), t, p1, p2);
}

/// 3
template<typename T, typename P1, typename P2, typename P3 >
static inline void group_call_helper(empty_list, T&, P1, P2, P3)
{
}

template<typename L, typename R, typename T, typename P1, typename P2, typename P3 >
static inline void group_call_helper(type_list<L, R>, T& t, P1 p1, P2 p2, P3 p3)
{
  t.get_aspect().template get<L>()(t, p1, p2, p3);
  group_call_helper( R(), t, p1, p2, p3);
}

/// 4
template<typename T, typename P1, typename P2, typename P3, typename P4 >
static inline void group_call_helper(empty_list, T&, P1, P2, P3, P4) 
{
}

template<typename L, typename R, typename T, typename P1, typename P2, typename P3, typename P4 >
static inline void group_call_helper(type_list<L, R>, T& t, P1 p1, P2 p2, P3 p3, P4 p4)
{
  t.get_aspect().template get<L>()(t, p1, p2, p3, p4);
  group_call_helper( R(), t, p1, p2, p3, p4);
}

/// 5
template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5 >
static inline void group_call_helper(empty_list, T&, P1, P2, P3, P4, P5)
{
}

template<typename L, typename R, typename T, typename P1, typename P2, typename P3, typename P4, typename P5 >
static inline void group_call_helper(type_list<L, R>, T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
{
  t.get_aspect().template get<L>()(t, p1, p2, p3, p4, p5);
  group_call_helper( R(), t, p1, p2, p3, p4, p5);
}

}; // group_helper
  
}}

#endif
