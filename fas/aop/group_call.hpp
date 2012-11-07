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

  /// TODO: переименовать в get_tags<TgList, T>
  /// TODO: специализация для get_tags<T, empty_type|emty_list > или  get_tags<empty_type|emty_list, T>- извлечение всех тегов аспектного класса, с равертываием групп

// строит из смешенного списка тегов (групп и обячных адвайсов),
// один плоский спискок, куда включенны адвайсы всех групп
template< typename TgList, typename T >
struct group_tags_getter1
{
  typedef typename head<TgList>::type head;
  typedef typename tail<TgList>::type tail;
  typedef type_list< head, tail> tag_list;
  typedef typename group_tags_getter1< tag_list, T >::type type;
};

template< typename L, typename R, typename T >
struct group_tags_getter1< fas::type_list<L, R>, T >
{
  typedef typename T::aspect::template select_group<L>::type group_tags;

  typedef typename fas::if_c<
    fas::some_type<group_tags, fas::empty_type>::value,
    L,
    group_tags
  >::type current_tags;

  typedef typename fas::merge<
    current_tags,
    typename group_tags_getter1< R, T >::type
  >::type type;
};

template< typename T >
struct group_tags_getter1< fas::empty_list, T >
{
  typedef fas::empty_list type;
};

template< typename TgList, typename T >
struct group_tags_getter
{
  typedef typename fas::normalize<TgList>::type tag_list;
  typedef typename group_tags_getter1<tag_list, T>::type type;
};

struct group_helper
{

  template<typename TgList, typename T, typename F>
  static inline F for_each( TgList, T& t, F f)
  {
    f(t, fas::tag<typename fas::head<TgList>::type>() );
    return for_each( typename fas::tail<TgList>::type(), t, f);
  }

  template<typename T, typename F>
  static inline F for_each( fas::empty_list, T&, F f ) { return f; }


  /// 0
  template<typename TgList, typename T>
  static inline void call( TgList, T& t)
  {
    t.get_aspect().template get< typename fas::head<TgList>::type >()(t);
    call( typename fas::tail<TgList>::type(), t);
  }

  template<typename T>
  static inline void call( fas::empty_list, T& ) { }

  /// 1
  template<typename TgList, typename T, typename P1>
  static inline void call( TgList, T& t, P1 p1)
  {
    t.get_aspect().template get< typename fas::head<TgList>::type >()(t, p1);
    call( typename fas::tail<TgList>::type(), t, p1);
  }

  template<typename T, typename P1>
  static inline void call( fas::empty_list, T&, P1 ) { }

  /// 2
  template<typename TgList, typename T, typename P1, typename P2>
  static inline void call( TgList, T& t, P1 p1, P2 p2)
  {
    t.get_aspect().template get< typename fas::head<TgList>::type >()(t, p1, p2);
    call( typename fas::tail<TgList>::type(), t, p1, p2);
  }

  template<typename T, typename P1, typename P2>
  static inline void call( fas::empty_list, T&, P1, P2 ) { }

  /// 3
  template<typename TgList, typename T, typename P1, typename P2, typename P3>
  static inline void call( TgList, T& t, P1 p1, P2 p2, P3 p3)
  {
    t.get_aspect().template get< typename fas::head<TgList>::type >()(t, p1, p2, p3);
    call( typename fas::tail<TgList>::type(), t, p1, p2, p3);
  }

  template<typename T, typename P1, typename P2, typename P3>
  static inline void call( fas::empty_list, T&, P1, P2, P3 ) { }

  /// 4
  template<typename TgList, typename T, typename P1, typename P2, typename P3, typename P4>
  static inline void call( TgList, T& t, P1 p1, P2 p2, P3 p3, P4 p4)
  {
    t.get_aspect().template get< typename fas::head<TgList>::type >()(t, p1, p2, p3, p4);
    call( typename fas::tail<TgList>::type(), t, p1, p2, p3, p4);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  static inline void call( fas::empty_list, T&, P1, P2, P3, P4 ) { }

  /// 5
  template<typename TgList, typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  static inline void call( TgList, T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
  {
    t.get_aspect().template get< typename fas::head<TgList>::type >()(t, p1, p2, p3, p4, p5);
    call( typename fas::tail<TgList>::type(), t, p1, p2, p3, p4, p5);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  static inline void call( fas::empty_list, T&, P1, P2, P3, P4, P5) { }
};

} // detail

template<typename TgList, typename T, typename F>
inline F group_for_each(T& t, F f)
{
  typedef typename detail::group_tags_getter< TgList, T>::type tag_list;
  return detail::group_helper::for_each( tag_list(), t, f);
}

template<typename TgList, typename T>
inline void group_call(T& t)
{
  typedef typename detail::group_tags_getter< TgList, T>::type tag_list;
  detail::group_helper::call( tag_list(), t);
}

template<typename TgList, typename T, typename P1>
inline void group_call(T& t, P1 p1)
{
  typedef typename detail::group_tags_getter< TgList, T>::type tag_list;
  detail::group_helper::call( tag_list(), t, p1);
}

template<typename TgList, typename T, typename P1, typename P2>
inline void group_call(T& t, P1 p1, P2 p2)
{
  typedef typename detail::group_tags_getter< TgList, T>::type tag_list;
  detail::group_helper::call( tag_list(), t, p1, p2);
}

template<typename TgList, typename T, typename P1, typename P2, typename P3>
inline void group_call(T& t, P1 p1, P2 p2, P3 p3)
{
  typedef typename detail::group_tags_getter< TgList, T>::type tag_list;
  detail::group_helper::call( tag_list(), t, p1, p2, p3);
}

template<typename TgList, typename T, typename P1, typename P2, typename P3, typename P4>
inline void group_call(T& t, P1 p1, P2 p2, P3 p3, P4 p4)
{
  typedef typename detail::group_tags_getter< TgList, T>::type tag_list;
  detail::group_helper::call( tag_list(),t, p1, p2, p3, p4);
}

template<typename TgList, typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
inline void group_call(T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5)
{
  typedef typename detail::group_tags_getter< TgList, T>::type tag_list;
  detail::group_helper::call( tag_list(), t, p1, p2, p3, p4, p5);
}

}

#endif
