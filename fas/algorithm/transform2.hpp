//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_TRANSFORM2_HPP
#define FAS_ALGORITHM_TRANSFORM2_HPP

#include "detail/transform2.hpp"
#include <fas/algorithm/algomacro.hpp>

namespace fas{

template<typename L1, typename L2, typename F >
struct transform2
{
  /*
#ifndef FAS_ALGORITHM_LAMBDA_CAST
  typedef typename detail::transform2_helper<L1, L2, FAS_T_SIMPLIFY(F) >::type type;
#else
  */
  typedef typename detail::transform2_helper_t<L1, L2, lambda<FAS_T_SIMPLIFY(F)>::template apply >::type type;
//#endif
};

template<typename L1, typename L2, template<typename, typename> class F >
struct transform2_t
{
  typedef typename detail::transform2_helper_t<L1, L2, F >::type type;
};

}


#endif
