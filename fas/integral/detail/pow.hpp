//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2020
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_DETAIL_POW_HPP
#define FAS_IMPLEMENTATION_DETAIL_POW_HPP

#include <fas/integral/integral_c.hpp>

namespace fas{ namespace detail{

  template<typename T, T base, int exp>
  struct pow_impl;

  template<typename T, T base>
  struct pow_impl<T, base, 1>
  {
    typedef integral_c<T, base> type;
    enum { value = type::value };
  };

  template<typename T, T base>
  struct pow_impl<T, base, 0>
  {
    typedef integral_c<T, 1> type;
    enum { value = type::value };
  };

  template<typename T, T base, int exp>
  struct pow_impl
  {
    typedef integral_c<
      T,
      base * pow_impl<T, base, exp-1>::value
    > type;
    enum { value = type::value };
  };

}}

#endif
