//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_SELECT_HPP
#define FAS_AOP_ASPECT_SELECT_HPP

#include <fas/aop/detail/aspect_select.hpp>

#include <fas/algorithm/any.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{

template<typename A, template<typename> class F = any >
struct aspect_select_t
{
  typedef typename detail::aspect_select_impl<A, F>::type type;
};

template<typename A, typename F = any<_> >
struct aspect_select
{
  typedef typename aspect_select_t<A, lambda<F, 1>::template apply>::type type;
};

}

#endif
