//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_TRANSFORM_HPP
#define FAS_ALGORITHM_DETAIL_TRANSFORM_HPP

#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/errorlist.hpp>
#include <fas/type_list/metalist.hpp>

#include <fas/static_check/static_error.hpp>


namespace fas{ namespace detail{

template<typename L, template<typename> class F>
struct transform_impl_t;

template<typename MT, typename L, template<typename> class F>
struct transform_impl2_t;

#ifdef FASLIB_TYPE_LIST_CHECK


template<typename L, template<typename> class F>
struct transform_helper_t
  : static_error< errorlist::not_type_list, is_type_list<L>::value >::type
  , static_error< errorlist::not_organized, is_organized<L>::value >::type
  , transform_impl_t<L, F>
{
};

#else

template<typename L, template<typename> class F>
struct transform_helper_t
  : transform_impl_t<L, F>
{
};

#endif

template<typename L, template<typename> class F>
struct transform_impl_t
  : transform_impl2_t<typename L::metatype, L, F>
{};

#ifndef DISABLE_TYPE_LIST_SPEC

template<template<typename> class F>
struct transform_impl_t<empty_list, F>
{
  typedef empty_list type;
};

template<typename L, typename R, template<typename> class F>
struct transform_impl_t< type_list<L, R>, F>
{
  typedef type_list< 
    typename F<L>::type,
    typename transform_impl_t< R, F>::type
  > type;
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename> class F>
struct transform_impl2_t< metalist::type_list, L, F>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;

  typedef type_list<
    typename F<head>::type,
    typename transform_impl_t< tail, F>::type
  > type;
};

template<typename L, template<typename> class F>
struct transform_impl2_t< metalist::empty_list, L, F>
{
  typedef L type;
};

}}


#endif
