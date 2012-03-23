//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_IS_SORTED_HPP
#define FAS_ALGORITHM_DETAIL_IS_SORTED_HPP

#include <fas/mp/apply.hpp>
#include <fas/static_check/verifying.hpp>
#include <fas/type_list/check_list.hpp>
#include <fas/type_list/metalist.hpp>

namespace fas{ namespace detail{

template<typename L, typename F, int>
struct is_sorted_impl;

template<typename L, typename F>
struct is_sorted_impl1;

template<typename M, typename L, typename F>
struct is_sorted_impl2;

template<typename H, typename L, typename F>
struct is_sorted_impl3;

template<typename M, typename L, typename F>
struct is_sorted_impl4;

template<typename L, typename F>
struct is_sorted_helper
{
  enum { value = is_sorted_impl< L, F, is_type_list<L>::value >::value };
};

template<typename L, typename F>
struct is_sorted_impl<L, F, false>
{
  enum { value = 1 };
};

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L, typename F, int>
struct is_sorted_verifying;

template<typename L, typename F, int I>
struct is_sorted_impl
  : verifying< is_sorted_verifying<L, F, I>, check_list<L> >::type
{
};

template<typename L, typename F, int>
struct is_sorted_verifying
  : is_sorted_impl1<L, F>
{
};

#else

template<typename L, typename F, int>
struct is_sorted_impl
  : is_sorted_impl1< L, F>
{
};

#endif

template<typename L, typename F>
struct is_sorted_impl1
  : is_sorted_impl2<typename L::metatype, L, F>
{
};


#ifndef DISABLE_TYPE_LIST_SPEC

template<typename F>
struct is_sorted_impl1<empty_list, F>
{
  enum { value = 1 };
};

/*
template<typename F>
struct is_sorted_impl1<el, F>
{
  enum { value = 1 };
};
*/

template<typename L, typename R, typename F>
struct is_sorted_impl1< type_list<L, R>, F >
{
  enum { value = is_sorted_impl3<R, type_list<L, R>, F>::value };
};

/*
template<typename L, typename R, typename F>
struct is_sorted_impl1< tl<L, R>, F >
{
  enum { value = is_sorted_impl3<R, tl<L, R>, F>::value };
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, typename F>
struct is_sorted_impl2<metalist::type_list, L, F>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  enum { value = is_sorted_impl3<tail, L, F>::value };
};

template<typename L, typename F>
struct is_sorted_impl2<metalist::empty_list, L, F>
{
  enum { value = 1 };
};

template<typename H, typename L, typename F>
struct is_sorted_impl3
  : is_sorted_impl4<typename H::metatype, L, F>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename F>
struct is_sorted_impl3<empty_list, L, F>
{
  enum { value = 1 };
};

/*
template<typename L, typename F>
struct is_sorted_impl3<el, L, F>
{
  enum { value = 1 };
};
*/

template<typename TL, typename TR, typename HL, typename HR, typename F>
struct is_sorted_impl3< type_list<TL, TR>, type_list<HL, HR>, F >
{
  // HR == tl<TL, TR>
  enum 
  { 
    value = ( apply<F, HL, TL>::type::value 
            || !apply<F, TL, HL>::type::value)
            && is_sorted_impl1< type_list<TL, TR>, F>::value
    
  };
};


/*
template<typename TL, typename TR, typename HL, typename HR, typename F>
struct is_sorted_impl3< tl<TL, TR>, tl<HL, HR>, F >
{
  // HR == tl<TL, TR>
  enum 
  { 
    value = ( apply<F, HL, TL>::type::value 
            || !apply<F, TL, HL>::type::value)
            && is_sorted_impl1< tl<TL, TR>, F>::value
    
  };
};
*/


#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, typename F>
struct is_sorted_impl4<metalist::type_list, L, F>
{
  typedef typename L::left_type first;
  typedef typename L::right_type tail;
  typedef typename tail::left_type second;
  enum 
  { 
    value = ( apply<F, first, second>::type::value 
            || !apply<F, second, first>::type::value)
            && is_sorted_impl1<tail, F>::value
    
  };
};

template<typename L, typename F>
struct is_sorted_impl4<metalist::empty_list, L, F>
{
  enum { value = 1 };
};



/// ////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////
/// ////////////////////////////////////////////////////////


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
