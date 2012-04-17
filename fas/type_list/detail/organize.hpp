//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_ORGANIZE_HPP
#define FAS_TYPE_LIST_DETAIL_ORGANIZE_HPP

#include <fas/type_list/merge.hpp>
#include <fas/static_check/verifying.hpp>
#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

#include <fas/type_list/is_type_list.hpp>
#include <fas/type_list/is_organized.hpp>


namespace fas{ namespace detail{


template< typename L >
struct organize_impl0;

template< typename M, typename L >
struct organize_impl1;

template< typename L, int B1 >
struct organize_impl2;

template< typename L, int B1, int B2 >
struct organize_impl3;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L>
struct organize_verifying;

template<typename L>
struct organize_helper
  : verifying< organize_verifying<L>, is_type_list<L> >::type
{
};

template<typename L>
struct organize_verifying
  : organize_impl0<L>
{
};

#else

template<typename L>
struct organize_helper
  : organize_impl0<L>
{
};

#endif

template< typename L >
struct organize_impl0
  : organize_impl1<typename L::metatype, L>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<>
struct organize_impl0<empty_list>
{
  typedef empty_list type;
};

template<typename L, typename R>
struct organize_impl0< type_list<L, R> >
{
  typedef typename organize_impl2< type_list<L, R>, is_organized< type_list<L, R> >::value >::type type;
};

#endif // DISABLE_TYPE_LIST_SPEC

template< typename L>
struct organize_impl1<metalist::empty_list, L>
{
  typedef L type;
};

template< typename L>
struct organize_impl1< metalist::type_list,  L>
{
  typedef typename organize_impl2<L, is_organized<L>::value >::type type;
};

// ok L организован
template< typename L, int>
struct organize_impl2
{
  typedef L type;
};

template< typename L>
struct organize_impl2<L, false>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  typedef typename organize_impl3<L, is_type_list<head>::value, is_type_list<tail>::value>::type type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template< typename L, typename R>
struct organize_impl2< type_list<L, R>, false>
{
  typedef typename organize_impl3< type_list<L, R> , is_type_list<L>::value, is_type_list<R>::value>::type type;
};

#endif // DISABLE_TYPE_LIST_SPEC

// ок, слева не список, а справа список
template< typename L>
struct organize_impl3<L, false, true>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;

  typedef type_list<
      head,
      typename organize_impl0<tail>::type
  > type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template< typename L, typename R>
struct organize_impl3< type_list<L, R>, false, true>
{
  typedef type_list< L, typename organize_impl0<R>::type> type;
};

#endif // DISABLE_TYPE_LIST_SPEC

// с двух сторон списки 
template< typename L>
struct organize_impl3<L, true, true>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  typedef typename merge<
      typename organize_impl0<head>::type,
      typename organize_impl0<tail>::type
  >::type type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template< typename L, typename R>
struct organize_impl3< type_list<L, R>, true, true>
{
  typedef typename merge<
      typename organize_impl0<L>::type,
      typename organize_impl0<R>::type
  >::type type;
};

#endif // DISABLE_TYPE_LIST_SPEC

// список слева, а справа нет
template< typename L>
struct organize_impl3<L, true, false>
{
  typedef typename L::left_type head;
  typedef type_list< 
    typename L::right_type, 
    empty_list 
  > tail;

  typedef typename merge<
      typename organize_impl0<head>::type,
      typename organize_impl0<tail>::type
  >::type type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template< typename L, typename R>
struct organize_impl3< type_list<L, R>, true, false>
{
  typedef typename merge<
      typename organize_impl0<L>::type,
      typename organize_impl0<type_list<R> >::type
  >::type type;
};

#endif // DISABLE_TYPE_LIST_SPEC

// с двух сторон не списки типов 
template< typename L>
struct organize_impl3<L, false, false>
{
  typedef typename L::left_type head;
  typedef typename L::right_type tail;

  typedef type_list<
    head,
    type_list<
      tail,
      empty_list
    >
  > type;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template< typename L, typename R>
struct organize_impl3< type_list<L, R>, false, false>
{
  typedef type_list<L, type_list<R> > type;
};

#endif // DISABLE_TYPE_LIST_SPEC

}}


#endif
