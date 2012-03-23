// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_LAMBDA_HPP
#define FAS_MP_LAMBDA_HPP

#include <fas/mp/ph_max.hpp>
#include <fas/mp/apply.hpp>
//#include <fas/mp/simplify.hpp>
#include <fas/mp/has_apply.hpp>

namespace fas{
  
namespace detail
{

template<typename F, int C>
struct lambda_impl0
  : F
{
  //typedef F type;
};

template<typename F>
struct lambda_impl0<F, 0>
{
  struct apply
  {
    typedef typename apply0<F>::type type;
  };
};

  
template<typename F, int C, int U>
struct lambda_impl;

template<typename F, int U>
struct lambda_impl<F, 0, U>
  : lambda_impl0< F, has_apply<F, U>::value > 
{
};

template<typename F, int U>
struct lambda_impl<F, 1, U>
{
  template<typename P1>
  struct apply
  {
    typedef typename apply1<F, P1>::type type;
  };
};

template<typename F, int U>
struct lambda_impl<F, 2, U>
{
  template<typename P1, typename P2>
  struct apply
  {
    typedef typename apply2<F, P1, P2>::type type;
  };
};

template<typename F, int U>
struct lambda_impl<F, 3, U>
{
  template<typename P1, typename P2, typename P3>
  struct apply
  {
    typedef typename apply3<F, P1, P2, P3>::type type;
  };
};

template<typename F, int U>
struct lambda_impl<F, 4, U>
{
  template<typename P1, typename P2, typename P3, typename P4>
  struct apply
  {
    typedef typename apply4<F, P1, P2, P3, P4>::type type;
  };
};

template<typename F, int U>
struct lambda_impl<F, 5, U>
{
  template<typename P1, typename P2, typename P3, typename P4, typename P5>
  struct apply
  {
    typedef typename apply5<F, P1, P2, P3, P4, P5>::type type;
  };
};

template<typename F, int R, int B>
struct lambda_impl_r: F
{
};

template<typename F, int R>
struct lambda_impl_r<F, R, 0>
  : lambda_impl< F, R, -1> 
{
};


}

template<typename F, int R = 1>
struct lambda : detail::lambda_impl< F, ph_max<F>::value, R >
{
};

template<typename F, int R>
struct lambda_r : detail::lambda_impl_r< F, R, has_apply<F, R>::value >
{
};

}

#endif
