//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_LAMBDA_HPP
#define FAS_MP_LAMBDA_HPP

#include <fas/mp/detail/lambda.hpp>

#include <fas/mp/private/ph_max.hpp>
#include <fas/mp/has_apply.hpp>

namespace fas{

template<typename F, int R = 1>
struct lambda 
  : detail::lambda_impl< F, ph_max<F>::value, R >
{
};

template<typename F, int R>
struct lambda_r 
  : detail::lambda_impl_r< F, R, has_apply<F, R>::value >
{
};

}

#endif
