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
  
  template<typename T, typename P1>
  typename apply<T>::type operator()(T& t, P1 p1) const
  {
    return M(&t, p1);
  }
  
  template<typename T, typename P1, typename P2>
  typename apply<T>::type operator()(T& t, P1 p1, P2 p2) const
  {
    return M(&t, p1, p2);
  }

  template<typename T, typename P1, typename P2, typename P3>
  typename apply<T>::type operator()(T& t, P1 p1, P2 p2, P3 p3) const
  {
    return M(&t, p1, p2, p3);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  typename apply<T>::type operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4) const
  {
    return M(&t, p1, p2, p3, p4);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  typename apply<T>::type operator()(T& t, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const
  {
    return M(&t, p1, p2, p3, p4, p5);
  }
};


template<typename M >
struct creator
{
  template<typename T>
  struct apply
  {
    typedef M type;
  };
  
  template<typename T>
  M operator()(T&) const
  {
    return M();
  }

  template<typename T, typename P1>
  M operator()(T&, P1 p1) const
  {
    return M(p1);
  }
  
  template<typename T, typename P1, typename P2>
  M operator()(T&, P1 p1, P2 p2) const
  {
    return M(p1, p2);
  }

  template<typename T, typename P1, typename P2, typename P3>
  M operator()(T&, P1 p1, P2 p2, P3 p3) const
  {
    return M(p1, p2, p3);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  M operator()(T&, P1 p1, P2 p2, P3 p3, P3 p4) const
  {
    return M(p1, p2, p3, p4);
  }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  M operator()(T&, P1 p1, P2 p2, P3 p3, P4 p4, P5 p5) const
  {
    return M(p1, p2, p3, p4, p5);
  }
};


}

#endif
