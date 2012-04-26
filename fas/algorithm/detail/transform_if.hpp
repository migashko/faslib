//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_TRANSFORM_IF_HPP
#define FAS_ALGORITHM_DETAIL_TRANSFORM_IF_HPP

#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/errorlist.hpp>
#include <fas/type_list/metalist.hpp>

#include <fas/static_check/static_error.hpp>


namespace fas{ namespace detail{

template<typename L, template<typename> class F, template<typename> class IF, int>
struct transform_if_impl1_t;

template<typename L, template<typename> class F, template<typename> class IF, int>
struct transform_if_impl3_t;

template<typename L, template<typename> class F, template<typename> class IF>
struct transform_if_impl_t;

template<typename MT, typename L, template<typename> class F, template<typename> class IF>
struct transform_if_impl2_t;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L, template<typename> class F, template<typename> class IF>
struct transform_if_helper_t
  : static_error< errorlist::not_type_list, is_type_list<L>::value >::type
  , static_error< errorlist::not_organized, is_organized<L>::value >::type
  , transform_if_impl_t<L, F, IF>
{
};

#else

template<typename L, template<typename> class F, template<typename> class IF>
struct transform_if_helper_t
  : transform_if_impl_t<L, F, IF>
{
};

#endif

template<typename L, template<typename> class F, template<typename> class IF>
struct transform_if_impl_t
  : transform_if_impl2_t<typename L::metatype, L, F, IF>
{};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R, template<typename> class F, template<typename> class IF>
struct transform_if_impl_t< type_list<L, R>, F, IF >
  : transform_if_impl1_t< type_list<L, R>, F, IF, IF<L>::type::value >
{
};

template<template<typename> class F, template<typename> class IF>
struct transform_if_impl_t< empty_list, F, IF >
{
  typedef empty_list type;
};


template<typename L, typename R, template<typename> class F, template<typename> class IF, int B>
struct transform_if_impl1_t< type_list<L, R>, F, IF, B>
{
  typedef type_list< 
    typename F<L>::type,
    typename transform_if_impl_t< R, F, IF>::type
  > type;
};

template<typename L, typename R, template<typename> class F, template<typename> class IF>
struct transform_if_impl1_t< type_list<L, R>, F, IF, false>
{
  typedef type_list< 
    L,
    typename transform_if_impl_t< R, F, IF>::type
  > type;
};


#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename> class F, template<typename> class IF>
struct transform_if_impl2_t< metalist::type_list, L, F, IF>
  : transform_if_impl3_t< L, F, IF, IF< typename L::left_type >::type::value  >
{
};

template<typename L, template<typename> class F, template<typename> class IF>
struct transform_if_impl2_t< metalist::empty_list, L, F, IF>
{
  typedef empty_list type;
};



template<typename L, template<typename> class F, template<typename> class IF, int B>
struct transform_if_impl3_t
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;

  typedef type_list<
    typename F<head>::type,
    typename transform_if_impl_t< tail, F, IF>::type
  > type;
};

template<typename L, template<typename> class F, template<typename> class IF>
struct transform_if_impl3_t< L, F, IF, false>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;

  typedef type_list<
    head,
    typename transform_if_impl_t< tail, F, IF>::type
  > type;
};

}}


#endif
