//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_SELECT_GROUP_HPP
#define FAS_AOP_DETAIL_SELECT_GROUP_HPP

#include <fas/aop/private/target_cast.hpp>
#include <fas/aop/private/find_advice.hpp>
#include <fas/aop/detail/has_advice.hpp>

#include <fas/type_list/head.hpp>
#include <fas/type_list/tail.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/normalize.hpp>
#include <fas/type_list/organize.hpp>
#include <fas/type_list/merge.hpp>

#include <fas/typemanip/if_c.hpp>
#include <fas/typemanip/empty_type.hpp>


namespace fas{ namespace detail{

template< typename TgList, typename A >
struct select_group_helper
{
  typedef typename head<TgList>::type head;
  typedef typename tail<TgList>::type tail;
  typedef type_list< head, tail> tag_list;
  typedef typename select_group_helper< tag_list, A >::type type;
};

template<typename, typename Adv, typename >
struct target_cast_or_tag
{
  typedef typename target_cast<Adv>::type type;
};

template<typename Tg, typename A>
struct target_cast_or_tag< Tg, empty_type, A >
{
  typedef typename if_c<
    detail::has_advice_aspect<Tg, A>::value,
    type_list<Tg>,
    empty_list
  >::type type;
};

template< typename L, typename R, typename A >
struct select_group_helper< fas::type_list<L, R>, A >
{
  typedef typename A::group_list group_list;
  typedef typename find_advice< L, group_list, empty_type >::type group_advice;
  typedef typename target_cast_or_tag< L, group_advice, A>::type tag_list;
  typedef typename fas::merge<
    tag_list,
    typename select_group_helper< R, A >::type
  >::type type;
};

template< typename A >
struct select_group_helper< fas::empty_list, A >
{
  typedef fas::empty_list type;
};


template< typename TgList, typename A >
struct select_group_aspect
{
  typedef typename normalize<TgList>::type tag_list;
  typedef typename organize<
    typename detail::select_group_helper<tag_list, A>::type
  >::type type;
};

}}

#endif
