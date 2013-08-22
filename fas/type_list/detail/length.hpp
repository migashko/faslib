//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_LENGTH_HPP
#define FAS_TYPE_LIST_DETAIL_LENGTH_HPP


#include <fas/type_list/metalist.hpp>
#include <fas/type_list/errorlist.hpp>

#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

#include <fas/static_check/static_error.hpp>

namespace fas{ namespace detail{

template<typename L>
struct length_impl1;

template<typename MT, typename L>
struct length_impl2;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L>
struct length_impl
  : static_error< errorlist::not_type_list, is_type_list<L>::value >::type
  , static_error< errorlist::not_organized, is_organized<L>::value >::type
  , length_impl1<L>
{
};

#else

template<typename L>
struct length_impl
  : length_impl1<L>
{
};

#endif

template<typename L>
struct length_impl1
  : length_impl2<typename L::metatype, L>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R>
struct length_impl1< type_list<L, R> >
{
  enum { value = 1 + length_impl1<R>::value };
};

template<>
struct length_impl1< empty_list >
{
  enum { value = 0 };
};

#endif

template<typename L>
struct length_impl2<metalist::type_list, L>
{
  typedef typename L::right_type tail;
  enum { value = 1 + length_impl1< tail>::value };
};

template<typename L>
struct length_impl2<metalist::empty_list, L>
{
  enum { value = 0 };
};

}}


#endif
