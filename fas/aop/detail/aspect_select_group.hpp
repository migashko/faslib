// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DETAIL_ASPECT_SELECT_GROUP_HPP
#define FAS_AOP_DETAIL_ASPECT_SELECT_GROUP_HPP

#include <fas/aop/metalist.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/merge.hpp>
#include <fas/type_list/unique.hpp>
//#include <fas/type_list/el.hpp>
#include <fas/mp/apply.hpp>
#include <fas/typemanip/if_c.hpp>


namespace fas{ namespace detail{
  
template<typename M, typename L, typename Tg>
struct aspect_select_group_impl;

template<typename M, typename T, typename EL, typename Tg>
struct aspect_select_group_impl2;

template<int, typename T, typename EL>
struct aspect_select_group_impl3;

template<typename L, typename Tg>
struct aspect_select_group_helper
{
  typedef typename aspect_select_group_impl<typename L::metatype, L, Tg>::type all_tag;
  typedef typename unique<all_tag>::type type;
};

template<typename L, typename Tg>
struct aspect_select_group_impl< metalist::empty_list, L, Tg>
{
  typedef empty_list type;
};

template<typename L, typename Tg>
struct aspect_select_group_impl< metalist::type_list, L, Tg>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  typedef typename merge<
    typename aspect_select_group_impl2< typename head::metatype, head, empty_list, Tg>::type,
    typename aspect_select_group_helper< tail, Tg>::type
  >::type type;

};

template<typename A, typename Tg>
struct aspect_select_group_impl< metalist::aspect, A, Tg>
{
  typedef typename aspect_select_group_helper< typename A::type_list, Tg>::type type;
};

template<typename T, typename Tg>
struct aspect_select_group_impl< metalist::advice, T, Tg>
{
  typedef empty_list type;
};

template<typename M, typename T, typename EL, typename Tg>
struct aspect_select_group_impl2
{
  typedef EL type;
};

template<typename G, typename EL, typename Tg>
struct aspect_select_group_impl2< metalist::group, G, EL, Tg>
{
  typedef typename aspect_select_group_impl3<
    is_has_tag<G, Tg>::value,
    G,
    EL
  >::type type;
};


template<typename A, typename EL, typename Tg>
struct aspect_select_group_impl2< metalist::aspect, A, EL, Tg>
{
  typedef typename aspect_select_group_helper< typename A::type_list, Tg>::type type;
};

template<int, typename T, typename EL>
struct aspect_select_group_impl3
{
  typedef typename T::target_list type;
};

template<typename T, typename EL>
struct aspect_select_group_impl3<false, T, EL>
{
  typedef EL type;
};



}}

#endif
