//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_DETAIL_LENGTH_HPP
#define FAS_IMPLEMENTATION_DETAIL_LENGTH_HPP

#include <fas/static_check/verifying.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/check_list.hpp>

namespace fas{ namespace detail{

template<typename L>
struct length_impl;

template<typename MT, typename L>
struct length_impl1;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L>
struct length_verifying;

template<typename L>
struct length_helper
  : verifying< length_verifying<L>, check_list<L> >::type
{
};

template<typename L>
struct length_verifying
  : length_impl<L>
{
};

#else

template<typename L>
struct length_helper
  : length_impl<L>
{
};

#endif

template<typename L>
struct length_impl
  : length_impl1<typename L::metatype, L>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R>
struct length_impl< type_list<L, R> >
{
  enum { value = 1 + length_impl<R>::value };
};

/*
template<typename L, typename R>
struct length_impl< tl<L, R> >
{
  enum { value = 1 + length_impl<R>::value };
};
*/

template<>
struct length_impl< empty_list >
{
  enum { value = 0 };
};

/*
template<>
struct length_impl< el >
{
  enum { value = 0 };
};
*/

#endif

template<typename L>
struct length_impl1<metalist::type_list, L>
{
  typedef typename L::right_type tail;
  enum { value = 1 + length_impl< tail>::value };
};

template<typename L>
struct length_impl1<metalist::empty_list, L>
{
  enum { value = 0 };
};


}}


#endif
