//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_DETAIL_UNWRAP_HPP
#define FAS_TYPEMANIP_DETAIL_UNWRAP_HPP

#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/typemanip/metalist.hpp>

namespace fas{ namespace detail{


template<typename T>
struct unwrap_helper;

template<typename T, int>
struct unwrap_impl;

template<typename T>
struct unwrap_helper
{
  typedef typename unwrap_impl<T, is_has_metatype<T, metalist::wrapper>::value >::type type;
};

template<typename T, int>
struct unwrap_impl
{
  typedef typename T::original_type type;
};

template<typename T>
struct unwrap_impl<T, false>
{
  typedef T type;
};


}}

#endif
