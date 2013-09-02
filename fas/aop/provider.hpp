//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_PROVIDER_HPP
#define FAS_AOP_PROVIDER_HPP

#include <fas/aop/metalist.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/mp/w.hpp>

namespace fas{

template<typename Tg, template<typename> class P >
struct provider_t
{
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef provider_t<Tg, P> advice_class;
  
  advice_class& get_advice() { return *this;}
  const advice_class& get_advice() const { return *this;}

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

template<typename Tg, typename M >
struct provider;

template<typename Tg, typename M >
struct provider< Tg, w<M> >
{
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef provider<Tg, w<M> > advice_class;
  
  advice_class& get_advice() { return *this;}
  const advice_class& get_advice() const { return *this;}

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

}

#endif
