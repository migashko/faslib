//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_ERASE_IF_HPP
#define FAS_ALGORITHM_ERASE_IF_HPP

#include <fas/algorithm/select.hpp>
#include <fas/integral/not_.hpp>

namespace fas{

template<typename L, typename F >
struct erase_if
  : select< L, not_<F> >
{
};

template<template<typename> class F >
struct make_not
{
  template<typename T>
  struct make: not_< F<T> > {};
};

template<typename L, template<typename> class F >
struct erase_if_t
  : select_t< L, make_not<F>::template make >
{
  
};

}

#endif
