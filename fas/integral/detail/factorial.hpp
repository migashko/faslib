//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_DETAIL_FACTORIAL_HPP
#define FAS_IMPLEMENTATION_DETAIL_FACTORIAL_HPP

/*
#include <fas/type_traits.hpp>
#include <fas/metalist.hpp>
#include <fas/verifying.hpp>
#include <fas/type_list.hpp>
#include <fas/type_selection.hpp>
*/

namespace fas{ namespace detail{

template<int V>
struct factorial_impl;


template<int V, bool>
struct factorial_helper;

template<int V>
struct factorial_helper<V, false>
  : factorial_impl<V>
{
};

template<>
struct factorial_impl<0>
{
  enum { value = 1};
};

template<>
struct factorial_impl<1>
{
  enum { value = 1};
};

template<int V>
struct factorial_impl
{
  enum { value = V * factorial_impl<V-1>::value };
};

/*
template<typename MT, typename L>
struct length_impl;

template<typename L, int, typename E>
struct length_helper_verifying;


template<typename L>
struct length_helper
  : length_helper_verifying<L, check_list<L>::value, typename check_list<L>::error>
{
};

template<typename L, int C, typename E>
struct length_helper_verifying
  : verifying<C, E>
  , length_impl<typename L::metatype, L>
{
};

template<typename L, typename E>
struct length_helper_verifying<L, false, E>
  //: if_c< is_placeholder<L>::value, empty_list, verifying<false, E> >::type
  :  verifying<false, E>
{
  enum { value = -1 };
};


template<typename L>
struct length_impl<metalist::type_list, L>
{
  typedef typename L::right_type tail;
  enum { value = 1 + length_impl<typename tail::metatype, tail>::value };
};

template<typename L>
struct length_impl<metalist::, L>
{
  enum { value = 0 };
};

*/
}}


#endif
