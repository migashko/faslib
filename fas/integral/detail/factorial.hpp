//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011, 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_DETAIL_FACTORIAL_HPP
#define FAS_IMPLEMENTATION_DETAIL_FACTORIAL_HPP

#include <fas/integral/times.hpp>
#include <fas/integral/integral_c.hpp>

namespace fas{ namespace detail{

template<typename VT, VT v, int>
struct factorial_impl;


template<typename VT, VT v, bool>
struct factorial_helper;

template<typename VT, VT v>
struct factorial_helper<VT, v, false>
  : factorial_impl<VT, v, static_cast<int>(v) >
{
};

template<typename VT, VT v>
struct factorial_impl<VT, v, 0 >
{
  typedef integral_c< VT, 1 > type;
};

template<typename VT, VT v>
struct factorial_impl<VT, v, 1>
{
  typedef integral_c< VT, 1 > type;
};

template<typename VT, VT v, int N>
struct factorial_impl
{
  typedef typename times<
    integral_c< VT, v >,
    typename factorial_impl<VT, v-1, N - 1>::type
  >::type type;
};


}}


#endif
