// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_SELECT_HPP
#define FAS_AOP_ASPECT_SELECT_HPP

//#include <fas/typemanip/empty_type.hpp>
//#include "detail/aspect_select.hpp"
#include <fas/aop/aspect_select_t.hpp>
#include <fas/algorithm/any.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/aop/detail/aspect_select_t.hpp>


namespace fas{

template<typename A, template<typename> class F = any >
struct aspect_select_t
{
  typedef typename detail::aspect_select_t_helper<A, F>::type type;
};

template<typename A, typename F = any<_> >
struct aspect_select
{
  typedef typename aspect_select_t<A, lambda<F, 1>::template apply>::type type;
};

/**для empty_type отдельная специализация*/

    /*template<typename A, typename F = empty_type>
struct aspect_select
{
  typedef typename detail::aspect_select_helper<A, F>::type type;
};*/

/*
template<typename A>
struct aspect_select_all
{
  typedef typename detail::aspect_select_helper<A, empty_type>::type type;
};
*/

}

#endif
