// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_HIERARCHY_DETAIL_SCATTER_HIERARCHY_HPP
#define FAS_HIERARCHY_DETAIL_SCATTER_HIERARCHY_HPP

#include <fas/type_list/metalist.hpp>
#include <fas/type_list/errorlist.hpp>

#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

#include <fas/static_check/static_error.hpp>



namespace fas{ namespace detail{

template<typename L>
struct sh;

template<typename L>
struct scatter_hierarchy_impl;

template<typename MT, typename L>
struct scatter_hierarchy_impl1;

#ifdef FASLIB_TYPE_LIST_CHECK


template<typename L>
struct scatter_hierarchy_helper
  : static_error< errorlist::not_type_list, is_type_list<L>::value >::type
  , static_error< errorlist::not_organized, is_organized<L>::value >::type
  , scatter_hierarchy_impl<L>
{
};

#else

template<typename L>
struct scatter_hierarchy_helper
  : scatter_hierarchy_impl<L>
{
};

#endif

template<typename L>
struct scatter_hierarchy_impl
  :  scatter_hierarchy_impl1<typename L::metatype, L>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC
template<typename L, typename R>
struct scatter_hierarchy_impl< type_list<L, R> >
{
  typedef sh< type_list<L, R> > type;
};

template<>
struct scatter_hierarchy_impl< empty_list >
{
  typedef sh< empty_list > type;
};
#endif

template< typename L>
struct scatter_hierarchy_impl1<metalist::type_list, L>
{
  typedef sh<L> type;
};

template< typename L>
struct scatter_hierarchy_impl1<metalist::empty_list, L>
{
  typedef sh<empty_list> type;
};

template<typename L>
struct sh
  : L::left_type
  , scatter_hierarchy_impl<typename L::right_type>::type
{
  typedef L type_list_type;
  typedef typename L::left_type left_base;
  typedef typename scatter_hierarchy_impl<typename L::right_type>::type right_base;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R>
struct sh< type_list<L, R> >
  : L
  , scatter_hierarchy_impl<R>::type
{
  typedef type_list<L, R> type_list_type;
  typedef L left_base;
  typedef typename scatter_hierarchy_impl<R>::type right_base;
};

#endif

template<>
struct sh<empty_list>
{
};



  /*
template<typename L>
struct sh;

template<typename M, typename L>
struct scatter_hierarchy_impl;

template<typename L>
struct scatter_hierarchy_helper;

template<typename L >
struct scatter_hierarchy_helper
{
  typedef typename scatter_hierarchy_impl<typename L::metatype, L>::type type;
};

template< typename L>
struct scatter_hierarchy_impl<metalist::type_list, L>
{
  typedef sh<L> type;
};

template< typename L>
struct scatter_hierarchy_impl<metalist::empty_list, L>
{
  typedef sh<metalist::empty_list> type;
};

template<typename L>
struct sh
  : L::left_type
  , scatter_hierarchy_impl<typename L::right_type::metatype, typename L::right_type>::type
{
  typedef L type_list;
  typedef typename L::left_type left_base;
  typedef typename scatter_hierarchy_impl<typename L::right_type::metatype, typename L::right_type>::type right_base;
};

template<>
struct sh<metalist::empty_list>
{
};
  */

}}

#endif
