//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_TRANSFORM2_HPP
#define FAS_ALGORITHM_TRANSFORM2_HPP

#include <fas/algorithm/detail/transform2.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{

template<typename L1, typename L2, typename F >
struct transform2
{
  typedef typename detail::transform2_impl_t<L1, L2, lambda<FAS_T_SIMPLIFY(F), 2>::template apply >::type type;
};

template<typename L1, typename L2, template<typename, typename> class F >
struct transform2_t
{
  typedef typename detail::transform2_impl_t<L1, L2, F >::type type;
};

}

#endif
