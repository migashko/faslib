//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_IS_SORTED_HPP
#define FAS_ALGORITHM_DETAIL_IS_SORTED_HPP

#include <fas/mp/apply.hpp>
#include <fas/static_check/verifying.hpp>
#include <fas/type_list/check_list.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/is_type_list.hpp>

namespace fas{ namespace detail{

template<typename L, template<typename, typename> class F, int>
struct is_sorted_impl_t;

template<typename L, template<typename, typename> class F>
struct is_sorted_impl1_t;

template<typename M, typename L, template<typename, typename> class F>
struct is_sorted_impl2_t;

template<typename H, typename L, template<typename, typename> class F>
struct is_sorted_impl3_t;

template<typename M, typename L, template<typename, typename> class F>
struct is_sorted_impl4_t;

template<typename L, template<typename, typename> class F>
struct is_sorted_helper_t
{
  enum { value = is_sorted_impl_t< L, F, is_type_list<L>::value >::value };
};

template<typename L, template<typename, typename> class F>
struct is_sorted_impl_t<L, F, false>
{
  enum { value = 1 };
};

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L, template<typename, typename> class F, int>
struct is_sorted_verifying_t;

template<typename L, template<typename, typename> class F, int I>
struct is_sorted_impl_t
  : verifying< is_sorted_verifying_t<L, F, I>, check_list<L> >::type
{
};

template<typename L, template<typename, typename> class F, int>
struct is_sorted_verifying_t
  : is_sorted_impl1_t<L, F>
{
};

#else

template<typename L, template<typename, typename> class F, int>
struct is_sorted_impl_t
  : is_sorted_impl1_t< L, F>
{
};

#endif

template<typename L, template<typename, typename> class F>
struct is_sorted_impl1_t
  : is_sorted_impl2_t<typename L::metatype, L, F>
{
};


#ifndef DISABLE_TYPE_LIST_SPEC

template<template<typename, typename> class F>
struct is_sorted_impl1_t<empty_list, F>
{
  enum { value = 1 };
};

template<typename L, typename R, template<typename, typename> class F>
struct is_sorted_impl1_t< type_list<L, R>, F >
{
  enum { value = is_sorted_impl3_t<R, type_list<L, R>, F>::value };
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename, typename> class F>
struct is_sorted_impl2_t<metalist::type_list, L, F>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  enum { value = is_sorted_impl3_t<tail, L, F>::value };
};

template<typename L, template<typename, typename> class F>
struct is_sorted_impl2_t<metalist::empty_list, L, F>
{
  enum { value = 1 };
};

template<typename H, typename L, template<typename, typename> class F>
struct is_sorted_impl3_t
  : is_sorted_impl4_t<typename H::metatype, L, F>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename, typename> class F>
struct is_sorted_impl3_t<empty_list, L, F>
{
  enum { value = 1 };
};


template<typename TL, typename TR, typename HL, typename HR, template<typename, typename> class F>
struct is_sorted_impl3_t< type_list<TL, TR>, type_list<HL, HR>, F >
{
  enum 
  { 
    value = ( F<HL, TL>::type::value 
            || !F<TL, HL>::type::value)
            && is_sorted_impl1_t< type_list<TL, TR>, F>::value
    
  };
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename, typename> class F>
struct is_sorted_impl4_t<metalist::type_list, L, F>
{
  typedef typename L::left_type first;
  typedef typename L::right_type tail;
  typedef typename tail::left_type second;
  enum 
  { 
    value = ( F<first, second>::type::value 
            || !F<second, first>::type::value)
            && is_sorted_impl1_t<tail, F>::value
    
  };
};

template<typename L, template<typename, typename> class F>
struct is_sorted_impl4_t<metalist::empty_list, L, F>
{
  enum { value = 1 };
};

}}


#endif
