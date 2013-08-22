//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_COUNT_IF_HPP
#define FAS_ALGORITHM_DETAIL_COUNT_IF_HPP

#include <fas/type_list/errorlist.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>

#include <fas/static_check/static_error.hpp>

namespace fas{ namespace detail{

template<typename L, template<typename> class F >
struct count_if_impl1_t;

template<typename M, typename L, template<typename> class F >
struct count_if_impl2_t;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L, template<typename> class F>
struct count_if_impl_t
  : static_error< errorlist::not_type_list, is_type_list<L>::value >::type
  , static_error< errorlist::not_organized, is_organized<L>::value >::type
  , count_if_impl1_t<L, F>
{
};

#else

template<typename L, template<typename> class F>
struct count_if_impl_t
  : count_if_impl1_t<L, F>
{
};

#endif

template<typename L, template<typename> class F>
struct count_if_impl1_t
  : count_if_impl2_t<typename L::metatype, L, F>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R, template<typename> class F>
struct count_if_impl1_t<type_list<L, R>, F>
{
  enum 
  {
    value = F<L>::type::value + count_if_impl1_t<R, F>::value
  };

};

template<template<typename> class F>
struct count_if_impl1_t<empty_list, F>
{
  enum { value = 0 };
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename> class F>
struct count_if_impl2_t<metalist::type_list, L, F>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  enum 
  {
    value = F<head>::type::value + count_if_impl1_t<tail, F>::value
  };
};

template<typename L, template<typename> class F>
struct count_if_impl2_t<metalist::empty_list, L, F>
{
  enum { value = 0 };
};

}}


#endif
