//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_STATIC_CHECK_DETAIL_VERIFYING_HPP
#define FAS_STATIC_CHECK_DETAIL_VERIFYING_HPP

namespace fas{ namespace detail{

template<typename T, typename E, int >
struct verifying_impl;

template<typename T, typename CH >
struct verifying_helper
{
  typedef typename verifying_impl<T, typename CH::error, CH::value>::type type;
};

template<typename T, typename E >
struct verifying_impl<T, E, 0>
{
  typedef E type;
};

template<typename T, typename E, int >
struct verifying_impl
{
  typedef T type;
};

}}

#endif
