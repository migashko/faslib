//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_DETAIL_SPLIT_HPP
#define FAS_IMPLEMENTATION_DETAIL_SPLIT_HPP

#include <fas/static_check/verifying.hpp>
#include <fas/type_list/check_range_c.hpp>
#include <fas/type_list/length.hpp>

namespace fas{ 

/*template<typename L>
struct length_;*/

namespace detail{

template<int I, typename L, int N>
struct split_impl;

template<int I, typename L>
struct split_impl2;

#ifdef FASLIB_TYPE_LIST_CHECK

template<int I, typename L>
struct split_verifying;

template<int I,typename L>
struct split_helper
  : verifying< split_verifying<I, L>, check_range_c2<I, L> >::type
{
};

template<int I, typename L>
struct split_verifying
  : split_impl< I, L, length<L>::value>
{
};

#else

template<int I,typename L>
struct split_helper
  : split_impl< I, L, length<L>::value>
{
};

#endif

template<int I, typename L, int N>
struct split_impl
{
  typedef typename split_impl2<I, L >::left_list left_list;
  typedef typename split_impl2<I, L >::right_list right_list;
};

template<typename L, int N>
struct split_impl<0, L, N>
{
  typedef typename L::final_type left_list;
  typedef L right_list;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<int N>
struct split_impl<0, empty_list, N>
{
  typedef empty_list left_list;
  typedef empty_list right_list;
};

/*
template<int N>
struct split_impl<0, el, N>
{
  typedef el left_list;
  typedef el right_list;
};
*/

template<typename L, typename R, int N>
struct split_impl<0, type_list<L, R>, N>
{
  typedef empty_list left_list;
  typedef type_list<L, R> right_list;
};

/*
template<typename L, typename R, int N>
struct split_impl<0, tl<L, R>, N>
{
  typedef el left_list;
  typedef tl<L, R> right_list;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

template<typename L, int N>
struct split_impl<N, L, N>
{
  typedef L left_list;
  typedef typename L::final_type right_list;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R, int N>
struct split_impl<N, type_list<L, R>, N>
{
  typedef type_list<L, R> left_list;
  typedef empty_list right_list;
};

/*
template<typename L, typename R, int N>
struct split_impl<N, tl<L, R>, N>
{
  typedef tl<L, R> left_list;
  typedef el right_list;
};
*/

template<int N>
struct split_impl<N, empty_list, N>
{
  typedef empty_list left_list;
  typedef empty_list right_list;
};

/*
template<int N>
struct split_impl<N, el, N>
{
  typedef el left_list;
  typedef el right_list;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC


template<int I, typename L>
struct split_impl2
{
  
  typedef typename L::left_type head;
  typedef typename L::right_type tail;
  typedef split_impl2<I-1, tail> split_type;

  typedef typename split_type::right_list right_list;
  typedef typename L::template rebind<
      head,
      typename split_type::left_list
  >::type left_list;
};


#ifndef DISABLE_TYPE_LIST_SPEC

template<int I, typename L, typename R>
struct split_impl2<I, type_list<L, R> >
{
  typedef split_impl2<I-1, R> helper;
  typedef typename helper::right_list right_list;
  typedef type_list<L, typename helper::left_list> left_list;
};

/*
template<int I, typename L, typename R>
struct split_impl2<I, tl<L, R> >
{
  typedef split_impl2<I-1, R> helper;
  typedef typename helper::right_list right_list;
  typedef tl<L, typename helper::left_list> left_list;
};
*/


#endif // DISABLE_TYPE_LIST_SPEC

template<typename L>
struct split_impl2<0, L>
{
  typedef typename L::final_type left_list;
  typedef L right_list;
};

#ifndef DISABLE_TYPE_LIST_SPEC

/*
template<typename L, typename R>
struct split_impl2<0, tl<L, R> >
{
  typedef el left_list;
  typedef tl<L, R> right_list;
};
*/


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

/*
template<>
struct split_impl2<0, el>
{
  typedef el left_list;
  typedef el right_list;
};
*/

#endif // DISABLE_TYPE_LIST_SPEC

}}


#endif
