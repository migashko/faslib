//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_TRANSFORM_HPP
#define FAS_ALGORITHM_TRANSFORM_HPP

#include "detail/transform.hpp"
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{

template<typename L, typename F >
struct transform
{
/*#ifndef FAS_ALGORITHM_LAMBDA_CAST
  typedef typename detail::transform_helper<L, FAS_T_SIMPLIFY(F) >::type type;
#else
  */
  typedef typename detail::transform_helper_t<L, lambda<FAS_T_SIMPLIFY(F)>::template apply >::type type;
//#endif
};

template<typename L, template<typename> class F >
struct transform_t
{
  typedef typename detail::transform_helper_t<L, F >::type type;
};


}


#endif
