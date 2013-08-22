//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_SPLIT_HPP
#define FAS_TYPE_LIST_DETAIL_SPLIT_HPP

#include <fas/type_list/errorlist.hpp>
#include <fas/type_list/length.hpp>

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

#include <fas/static_check/static_error.hpp>

namespace fas{ namespace detail{

template<int I, typename L, int N>
struct split_impl1;

template<int I, typename L>
struct split_impl2;

#ifdef FASLIB_TYPE_LIST_CHECK

template<int I, typename L>
struct split_verifying;

template<int I,typename L>
struct split_impl
  : static_error< 
      errorlist::out_of_range< I, length<L>::value >, 
      ( (I>=0) && (I <= length<L>::value) )
    >::type
  , split_impl1< I, L, length<L>::value>
{
};

#else

template<int I,typename L>
struct split_impl
  : split_impl1< I, L, length<L>::value>
{
};

#endif

template<int I, typename L, int N>
struct split_impl1
{
  typedef typename split_impl2<I, L >::left_list left_list;
  typedef typename split_impl2<I, L >::right_list right_list;
};

template<typename L, int N>
struct split_impl1<0, L, N>
{
  typedef empty_list left_list;
  typedef L right_list;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<int N>
struct split_impl1<0, empty_list, N>
{
  typedef empty_list left_list;
  typedef empty_list right_list;
};

template<typename L, typename R, int N>
struct split_impl1<0, type_list<L, R>, N>
{
  typedef empty_list left_list;
  typedef type_list<L, R> right_list;
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, int N>
struct split_impl1<N, L, N>
{
  typedef L left_list;
  typedef empty_list right_list;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R, int N>
struct split_impl1<N, type_list<L, R>, N>
{
  typedef type_list<L, R> left_list;
  typedef empty_list right_list;
};

template<int N>
struct split_impl1<N, empty_list, N>
{
  typedef empty_list left_list;
  typedef empty_list right_list;
};

#endif // DISABLE_TYPE_LIST_SPEC


template<int I, typename L>
struct split_impl2
{
  
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  typedef split_impl2<I-1, tail> split_type;

  typedef typename split_type::right_list right_list;
  typedef type_list<
    head,
    typename split_type::left_list
  > left_list;
};


#ifndef DISABLE_TYPE_LIST_SPEC

template<int I, typename L, typename R>
struct split_impl2<I, type_list<L, R> >
{
  typedef split_impl2<I-1, R> helper;
  typedef typename helper::right_list right_list;
  typedef type_list<L, typename helper::left_list> left_list;
};

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L>
struct split_impl2<0, L>
{
  typedef empty_list left_list;
  typedef L right_list;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R>
struct split_impl2<0, type_list<L, R> >
{
  typedef empty_list left_list;
  typedef type_list<L, R> right_list;
};

template<>
struct split_impl2<0, empty_list>
{
  typedef empty_list left_list;
  typedef empty_list right_list;
};

#endif // DISABLE_TYPE_LIST_SPEC

}}


#endif
