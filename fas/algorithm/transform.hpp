//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_TRANSFORM_HPP
#define FAS_ALGORITHM_TRANSFORM_HPP

#include <fas/algorithm/detail/transform.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{

template<typename L, typename F >
struct transform
{
  typedef typename detail::transform_impl_t<L, lambda<FAS_T_SIMPLIFY(F)>::template apply >::type type;
};

template<typename L, template<typename> class F >
struct transform_t
{
  typedef typename detail::transform_impl_t<L, F >::type type;
};


}


#endif
