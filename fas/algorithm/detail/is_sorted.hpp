//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_IS_SORTED_HPP
#define FAS_ALGORITHM_DETAIL_IS_SORTED_HPP

#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>
#include <fas/type_list/errorlist.hpp>
#include <fas/type_list/metalist.hpp>

#include <fas/static_check/static_error.hpp>



namespace fas{ namespace detail{

template<typename L, template<typename, typename> class F, int>
struct is_sorted_impl1_t;

template<typename L, template<typename, typename> class F>
struct is_sorted_impl2_t;

template<typename M, typename L, template<typename, typename> class F>
struct is_sorted_impl3_t;

template<typename H, typename L, template<typename, typename> class F>
struct is_sorted_impl4_t;

template<typename M, typename L, template<typename, typename> class F>
struct is_sorted_impl5_t;

template<typename L, template<typename, typename> class F>
struct is_sorted_impl_t
{
  enum { value = is_sorted_impl1_t< L, F, is_type_list<L>::value >::value };
};

template<typename L, template<typename, typename> class F>
struct is_sorted_impl1_t<L, F, false>
{
  enum { value = 1 };
};

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L, template<typename, typename> class F, int I>
struct is_sorted_impl1_t
  : static_error< errorlist::not_type_list, is_type_list<L>::value >::type
  , static_error< errorlist::not_organized, is_organized<L>::value >::type
  , is_sorted_impl2_t<L, F>
{
};


#else

template<typename L, template<typename, typename> class F, int>
struct is_sorted_impl1_t
  : is_sorted_impl2_t< L, F>
{
};

#endif

template<typename L, template<typename, typename> class F>
struct is_sorted_impl2_t
  : is_sorted_impl3_t<typename L::metatype, L, F>
{
};


#ifndef DISABLE_TYPE_LIST_SPEC

template<template<typename, typename> class F>
struct is_sorted_impl2_t<empty_list, F>
{
  enum { value = 1 };
};

template<typename L, typename R, template<typename, typename> class F>
struct is_sorted_impl2_t< type_list<L, R>, F >
{
  enum { value = is_sorted_impl4_t<R, type_list<L, R>, F>::value };
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename, typename> class F>
struct is_sorted_impl3_t<metalist::type_list, L, F>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  enum { value = is_sorted_impl4_t<tail, L, F>::value };
};

template<typename L, template<typename, typename> class F>
struct is_sorted_impl3_t<metalist::empty_list, L, F>
{
  enum { value = 1 };
};

template<typename H, typename L, template<typename, typename> class F>
struct is_sorted_impl4_t
  : is_sorted_impl5_t<typename H::metatype, L, F>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename, typename> class F>
struct is_sorted_impl4_t<empty_list, L, F>
{
  enum { value = 1 };
};


template<typename TL, typename TR, typename HL, typename HR, template<typename, typename> class F>
struct is_sorted_impl4_t< type_list<TL, TR>, type_list<HL, HR>, F >
{
  enum 
  { 
    value = ( F<HL, TL>::type::value 
            || !F<TL, HL>::type::value)
            && is_sorted_impl2_t< type_list<TL, TR>, F>::value
    
  };
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename, typename> class F>
struct is_sorted_impl5_t<metalist::type_list, L, F>
{
  typedef typename L::left_type first;
  typedef typename L::right_type tail;
  typedef typename tail::left_type second;
  enum 
  { 
    value = ( F<first, second>::type::value 
            || !F<second, first>::type::value)
            && is_sorted_impl2_t<tail, F>::value
    
  };
};

template<typename L, template<typename, typename> class F>
struct is_sorted_impl5_t<metalist::empty_list, L, F>
{
  enum { value = 1 };
};

}}


#endif
