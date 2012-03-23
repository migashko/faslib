//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_DETAIL_TRANSFORM_HPP
#define FAS_ALGORITHM_DETAIL_TRANSFORM_HPP

#include <fas/mp/apply.hpp>
#include <fas/static_check/verifying.hpp>
#include <fas/type_list/check_list.hpp>
#include <fas/type_list/metalist.hpp>

namespace fas{ namespace detail{

template<typename L, typename F>
struct transform_impl;

template<typename MT, typename L, typename F>
struct transform_impl2;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L, typename F>
struct transform_verifying;

template<typename L, typename F>
struct transform_helper
  : verifying< transform_verifying<L, F>, check_list<L> >::type
{
};

template<typename L, typename F>
struct transform_verifying
  : transform_impl<L, F>
{
};

#else

template<typename L, typename F>
struct transform_helper
  : transform_impl<L, F>
{
};

#endif

template<typename L, typename F>
struct transform_impl
  : transform_impl2<typename L::metatype, L, F>
{};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename F>
struct transform_impl<empty_list, F>
{
  typedef empty_list type;
};

/*
template<typename F>
struct transform_impl<el, F>
{
  typedef el type;
};
*/

template<typename L, typename R, typename F>
struct transform_impl<type_list<L, R>, F>
{
  typedef type_list< 
    typename apply<F, L>::type,
    typename transform_impl< R, F>::type
  > type;
};

/*
template<typename L, typename R, typename F>
struct transform_impl<tl<L, R>, F>
{
  typedef tl< 
    typename apply<F, L>::type,
    typename transform_impl< R, F>::type
  > type;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, typename F>
struct transform_impl2<metalist::type_list, L, F>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;

  typedef typename L::template rebind<
        typename apply<F, head>::type,
        typename transform_impl< tail, F>::type
      >::type type;
};

template<typename L, typename F>
struct transform_impl2<metalist::empty_list, L, F>
{
  typedef L type;
};

/// ///////////////////////////////////////////////////////

template<typename L, template<typename> class F>
struct transform_impl_t;

template<typename MT, typename L, template<typename> class F>
struct transform_impl2_t;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L, template<typename> class F>
struct transform_verifying_t;

template<typename L, template<typename> class F>
struct transform_helper_t
  : verifying< transform_verifying_t<L, F>, check_list<L> >::type
{
};

template<typename L, template<typename> class F>
struct transform_verifying_t
  : transform_impl_t<L, F>
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
struct transform_impl_t<type_list<L, R>, F>
{
  typedef type_list< 
    typename F<L>::type,
    typename transform_impl_t< R, F>::type
  > type;
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, template<typename> class F>
struct transform_impl2_t<metalist::type_list, L, F>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;

  typedef typename L::template rebind<
        typename F<head>::type,
        typename transform_impl_t< tail, F>::type
      >::type type;
};

template<typename L, template<typename> class F>
struct transform_impl2_t<metalist::empty_list, L, F>
{
  typedef L type;
};


}}


#endif
