//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_TYPE_COUNT_HPP
#define FAS_TYPE_LIST_DETAIL_TYPE_COUNT_HPP

#include <fas/type_list/metalist.hpp>
#include <fas/type_list/errorlist.hpp>

#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

#include <fas/static_check/static_error.hpp>


namespace fas{ namespace detail{

template<typename T, typename L>
struct type_count_impl1;

template<typename MT, typename T, typename L>
struct type_count_impl2;

template<typename T1, typename T2>
struct type_count_some_type;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename T,typename L>
struct type_count_helper
  : static_error< errorlist::not_type_list, is_type_list<L>::value >::type
  , static_error< errorlist::not_organized, is_organized<L>::value >::type
  , type_count_impl1<T, L> 
{
};

#else

template<typename T, typename L>
struct type_count_helper
  : type_count_impl1< T, L>
{
};

#endif

template<typename T, typename L>
struct type_count_impl1
  : type_count_impl2<typename L::metatype, T, L>
{
  
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename T, typename L, typename R>
struct type_count_impl1<T, type_list<L, R> >
{
  enum 
  {
    value = type_count_some_type<T, L>::value 
        + type_count_impl1<T, R>::value 
  };
};

template<typename T>
struct type_count_impl1<T, empty_list>
{
  enum { value = 0 };
};


#endif // DISABLE_TYPE_LIST_SPEC

template<typename T, typename L>
struct type_count_impl2<metalist::type_list, T, L>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  enum 
  {
    value = type_count_some_type<T, head>::value 
        + type_count_impl1<T, tail>::value 
  };
};

template<typename T, typename L>
struct type_count_impl2<metalist::empty_list, T, L>
{
  enum { value = 0 };
};

template<typename T1, typename T2>
struct type_count_some_type
{
  enum { value = 0 };
};

template<typename T>
struct type_count_some_type<T, T>
{
  enum { value = 1 };
};

}}


#endif
