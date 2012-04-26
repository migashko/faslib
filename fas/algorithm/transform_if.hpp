//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_TRANSFORM_IF_HPP
#define FAS_ALGORITHM_TRANSFORM_IF_HPP

#include <fas/algorithm/detail/transform_if.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{

template<typename L, typename F, typename IF >
struct transform_if
{
  typedef typename detail::transform_if_helper_t<
    L, 
    lambda<FAS_T_SIMPLIFY(F)>::template apply,
    lambda<FAS_T_SIMPLIFY(IF)>::template apply 
  >::type type;
};

template<typename L, template<typename> class F, template<typename> class IF >
struct transform_if_t
{
  typedef typename detail::transform_if_helper_t<L, F, IF >::type type;
};


}


#endif
