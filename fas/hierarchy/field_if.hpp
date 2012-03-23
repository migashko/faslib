// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_HIERARCHY_FIELD_IF_HPP
#define FAS_HIERARCHY_FIELD_IF_HPP

#include "scatter_hierarchy.hpp"

#include <fas/type_list/type_at.hpp>
#include <fas/algorithm/index_of_if.hpp>
#include <fas/algorithm/find_if.hpp>

namespace fas{

template<typename F, typename H>
typename find_if< typename H::type_list_type, F>::type& field_if(H& h)
{
  typedef typename H::type_list_type type_list_type;
  typedef typename type_at< typename index_of_if<type_list_type, F>::type, type_list_type >::fulltail fulltail;
  return static_cast< detail::sh<fulltail> &>(h);
};

/*
template<typename F, typename L>
typename find_if<  L, F>::type& field_if(scatter_hierarchy<L>& h)
{
  typedef typename type_at< typename index_of_if<L, F>::type, L >::fulltail fulltail;
  return static_cast< detail::sh<fulltail> &>(h);
};
*/

template<template<typename> class F, typename H>
typename find_if_t< typename H::type_list_type, F>::type& field_if_t(H& h)
{
  typedef typename H::type_list_type type_list_type;
  typedef typename type_at< typename index_of_if_t<type_list_type, F>::type, type_list_type >::fulltail fulltail;
  return static_cast< detail::sh<fulltail> &>(h);
};

/*
template<template<typename> class F, typename L>
typename find_if_t< L, F>::type& field_if_t(scatter_hierarchy<L>& h)
{
  typedef typename type_at< typename index_of_if_t<L, F>::type, L >::fulltail fulltail;
  return static_cast< detail::sh<fulltail> &>(h);
};
*/


}

#endif
