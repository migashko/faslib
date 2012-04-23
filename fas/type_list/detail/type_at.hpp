//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_TYPE_AT_HPP
#define FAS_TYPE_LIST_DETAIL_TYPE_AT_HPP

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

#include <fas/type_list/errorlist.hpp>
#include <fas/type_list/length.hpp>

#include <fas/static_check/static_error.hpp>


namespace fas{ namespace detail{

template<int I, typename L>
struct type_at_impl;

#ifdef FASLIB_TYPE_LIST_CHECK

template<int I, typename L>
struct type_at_verifying;

template<int I,typename L>
struct type_at_helper
  : static_error< 
      errorlist::out_of_range< I, length<L>::value >, 
      ( (I>=0) && (I < length<L>::value) )
    >::type
  , type_at_impl< I, L >

{
};

#else

template<int I,typename L>
struct type_at_helper
  : type_at_impl< I, L>
{
};

#endif


template<int I, typename L>
struct type_at_impl
{
  typedef typename type_at_impl< I-1, typename L::right_type>::type type;
  typedef typename type_at_impl< I-1, typename L::right_type>::tail tail;
  typedef typename type_at_impl< I-1, typename L::right_type>::fulltail fulltail;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<int I, typename L, typename R>
struct type_at_impl<I, type_list<L, R> >
{
  typedef typename type_at_impl< I-1, R>::type type;
  typedef typename type_at_impl< I-1, R>::tail tail;
  typedef typename type_at_impl< I-1, R>::fulltail fulltail;
};


#endif // DISABLE_TYPE_LIST_SPEC

template<typename L>
struct type_at_impl<0, L>
{
  // Доп. специализации на конц списка не нужны, т.к. производиться проверка на длину списка
  typedef typename L::left_type type;
  typedef typename L::right_type tail;
  typedef L fulltail;
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R>
struct type_at_impl<0, type_list<L, R> >
{
  // Доп. специализации на конц списка не нужны, т.к. производиться проверка на длину списка
  typedef L type;
  typedef R tail;
  typedef type_list<L, R> fulltail;
};


#endif // DISABLE_TYPE_LIST_SPEC

}}


#endif
