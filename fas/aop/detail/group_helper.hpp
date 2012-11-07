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
  F for_each( TgList, T& t, F f) const
  {
    f(t, tag<typename head<TgList>::type>() );
    return for_each( typename tail<TgList>::type(), t, f);
  }

  template<typename T, typename F>
  F for_each( empty_list, T&, F f )  const { return f; }

  /// 0
  template<typename TgList, typename T>
  void call( TgList, T& t) const
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t);
    call( typename tail<TgList>::type(), t);
  }

  template<typename T>
  void call( empty_list, T& ) const { }

  /// 1
  template<typename TgList, typename T, typename P1>
  void call( TgList, T& t, P1 p1) const
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t, p1);
    call( typename tail<TgList>::type(), t, p1);
  }

  template<typename T, typename P1>
  void call( empty_list, T&, P1 ) const { }

  /// 2
  template<typename TgList, typename T, typename P1, typename P2>
  void call( TgList, T& t, P1 p1, P2 p2) const
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t, p1, p2);
    call( typename tail<TgList>::type(), t, p1, p2);
  }

  template<typename T, typename P1, typename P2>
  void call( empty_list, T&, P1, P2 ) const { }

  /// 3
  template<typename TgList, typename T, typename P1, typename P2, typename P3>
  void call( TgList, T& t, P1 p1, P2 p2, P3 p3) const
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t, p1, p2, p3);
    call( typename tail<TgList>::type(), t, p1, p2, p3);
  }

  template<typename T, typename P1, typename P2, typename P3>
  void call( empty_list, T&, P1, P2, P3 ) const { }

  /// 4
  template<typename TgList, typename T, typename P1, typename P2, typename P3, typename P4>
  void call( TgList, T& t, P1 p1, P2 p2, P3 p3, P4 p4) const
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t, p1, p2, p3, p4);
    call( typename tail<TgList>::type(), t, p1, p2, p3, p4);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  void call( empty_list, T&, P1, P2, P3, P4 ) const { }

  /// 5
  template<typename TgList, typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  void call( TgList, T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const
  {
    t.get_aspect().template get< typename head<TgList>::type >()(t, p1, p2, p3, p4, p5);
    call( typename tail<TgList>::type(), t, p1, p2, p3, p4, p5);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  void call( empty_list, T&, P1, P2, P3, P4, P5) const { }
};

}}

#endif
