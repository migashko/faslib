//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_DETAIL_MERGE_ASPECT_HPP
#define FAS_AOP_ASPECT_DETAIL_MERGE_ASPECT_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/private/is_aspect.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/head.hpp>
#include <fas/type_list/length.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/typemanip/empty_type.hpp>

namespace fas{ namespace detail{

template<typename T, bool IsAspect>
struct aspect_pre
{
  typedef aspect<T> type;
};

template<>
struct aspect_pre<empty_list, false>
{
  typedef empty_list type;
};

template<>
struct aspect_pre<empty_type, false>
{
  typedef empty_list type;
};

template<typename A>
struct aspect_pre<A, true>
{
  typedef A type;
};

template<>
struct aspect_pre< aspect<empty_list>, true>
{
  typedef empty_list type;
};

template<>
struct aspect_pre< aspect<empty_type>, true>
{
  typedef empty_list type;
};

template<typename L, int I>
struct merge_aspect_impl
{
  typedef aspect< L > type;
};

template<typename L>
struct merge_aspect_impl< L, 0 >
{
  typedef aspect<> type;
};

template<typename A, bool B>
struct merge_aspect_impl2
{
  typedef A type;
};

template<typename L>
struct merge_aspect_impl2<L, false>
{
  typedef aspect<L> type;
};


template<typename L>
struct merge_aspect_impl< L, 1 >
{
  typedef typename head<L>::type item;
  typedef typename merge_aspect_impl2< item, is_aspect<item>::value >::type type;
};

template<typename A1, typename A2, typename A3, typename A4, typename A5>
struct merge_aspect
{
  typedef typename type_list_n<
    typename aspect_pre<A1, is_aspect<A1>::value >::type,
    typename aspect_pre<A2, is_aspect<A2>::value >::type,
    typename aspect_pre<A3, is_aspect<A3>::value >::type,
    typename aspect_pre<A4, is_aspect<A4>::value >::type,
    typename aspect_pre<A5, is_aspect<A5>::value >::type
  >::type param_list;

  typedef typename merge_aspect_impl<
    param_list,
    length<param_list>::value
  >::type type;
};

}}

#endif
