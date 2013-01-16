//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_PROVIDER_HPP
#define FAS_AOP_PROVIDER_HPP

#include <fas/mp/lambda.hpp>
#include <fas/mp/w.hpp>

namespace fas{

template<template<typename> class P >
struct provider_t
{
  template<typename T>
  struct apply
  {
    typedef P<T> type;
  };

  template<typename T>
  typename apply<T>::type operator()(T& t) const
  {
    return typename apply<T>::type(&t);
  }
};

template<typename M >
struct provider;

template<typename M >
struct provider< w<M> >
{
  template<typename T>
  struct apply
  {
    typedef typename fas::apply< M, T>::type type;
  };

  template<typename T>
  typename apply<T>::type operator()(T& t) const
  {
    return typename apply<T>::type(&t);
  }
};

}

#endif
