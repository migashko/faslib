//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DEATIL_GROUP_HELPER_HPP
#define FAS_AOP_DEATIL_GROUP_HELPER_HPP

#include <fas/aop/tag.hpp>

#include <fas/type_list/head.hpp>
#include <fas/type_list/tail.hpp>
#include <fas/type_list/empty_list.hpp>

namespace fas{ namespace detail{

struct group_helper
{
  template<typename TgList, typename T, typename F>
  static F for_each( TgList, T& t, F f)
  {
    f(t, tag<typename head<TgList>::type>() );
    return for_each( typename tail<TgList>::type(), t, f);
  }

  template<typename T, typename F>
  static F for_each( empty_list, T&, F f ) { return f; }

  /// 0
  template<typename TgList, typename T>
  static void call( TgList, T& t)
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t);
    call( typename tail<TgList>::type(), t);
  }

  template<typename T>
  static void call( empty_list, T& ) { }

  /// 1
  template<typename TgList, typename T, typename P1>
  static void call( TgList, T& t, P1 p1)
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t, p1);
    call( typename tail<TgList>::type(), t, p1);
  }

  template<typename T, typename P1>
  static void call( empty_list, T&, P1 ) { }

  /// 2
  template<typename TgList, typename T, typename P1, typename P2>
  static void call( TgList, T& t, P1 p1, P2 p2)
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t, p1, p2);
    call( typename tail<TgList>::type(), t, p1, p2);
  }

  template<typename T, typename P1, typename P2>
  static void call( empty_list, T&, P1, P2 ) { }

  /// 3
  template<typename TgList, typename T, typename P1, typename P2, typename P3>
  static void call( TgList, T& t, P1 p1, P2 p2, P3 p3)
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t, p1, p2, p3);
    call( typename tail<TgList>::type(), t, p1, p2, p3);
  }

  template<typename T, typename P1, typename P2, typename P3>
  static void call( empty_list, T&, P1, P2, P3 ) { }

  /// 4
  template<typename TgList, typename T, typename P1, typename P2, typename P3, typename P4>
  static void call( TgList, T& t, P1 p1, P2 p2, P3 p3, P4 p4)
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t, p1, p2, p3, p4);
    call( typename tail<TgList>::type(), t, p1, p2, p3, p4);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  static void call( empty_list, T&, P1, P2, P3, P4 ) { }

  /// 5
  template<typename TgList, typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  static void call( TgList, T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t, p1, p2, p3, p4, p5);
    call( typename tail<TgList>::type(), t, p1, p2, p3, p4, p5);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  static void call( empty_list, T&, P1, P2, P3, P4, P5) { }
};
  
}}

#endif
