//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_DETAIL_REVERSE_HPP
#define FAS_TYPE_LIST_DETAIL_REVERSE_HPP

#include <fas/type_list/length.hpp>
#include <fas/type_list/type_at_c.hpp>

#include <fas/static_check/verifying.hpp>
#include <fas/type_list/metalist.hpp>
#include <fas/type_list/check_list.hpp>

#include <fas/type_list/type_list.hpp>
#include <fas/type_list/empty_list.hpp>

namespace fas{ namespace detail{

template<typename L, int C >
struct reverse_impl;

template<typename L, int C >
struct reverse_impl;

template<typename MT, typename L, int C >
struct reverse_impl2;

#ifdef FASLIB_TYPE_LIST_CHECK

template<typename L>
struct reverse_verifying;

template<typename L>
struct reverse_helper
  : verifying< reverse_verifying<L>, check_list<L> >::type
{
};

template<typename L>
struct reverse_verifying
  : reverse_impl< L, length<L>::value - 1>
{
};

#else

template<typename L>
struct reverse_helper
  : reverse_impl< L, length<L>::value - 1>
{
};

#endif

template<typename L, int C >
struct reverse_impl
  : reverse_impl2< typename L::metatype, L, C>
{
};

#ifndef DISABLE_TYPE_LIST_SPEC

template<typename L, typename R, int C>
struct reverse_impl<type_list<L, R>, C>
{
  typedef type_list<
    typename type_at_c< C, type_list<L, R> >::type,
    typename reverse_impl< type_list<L, R>, C-1>::type
  > type;
};

template<typename L, typename R>
struct reverse_impl<type_list<L, R>, 0>
{
  typedef type_list<L> type;
};

template<>
struct reverse_impl<empty_list, -1>
{
  typedef empty_list type;
};

#endif // DISABLE_TYPE_LIST_SPEC


template<typename L, int C>
struct reverse_impl2<metalist::type_list, L, C>
{
  typedef type_list<
      typename type_at_c< C, L>::type,
      typename reverse_impl< L, C-1>::type
  > type;
};

template<typename L>
struct reverse_impl2<metalist::type_list, L, 0>
{
  typedef type_list<
      typename type_at_c<0, L>::type,
      empty_list
  > type;
};

template<typename L>
struct reverse_impl2<metalist::empty_list, L, -1>
{
  typedef L type;
};

}}


#endif
