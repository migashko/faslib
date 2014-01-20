//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2014
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_ACCUMULATE_HPP
#define FAS_ALGORITHM_ACCUMULATE_HPP

#include <fas/algorithm/detail/accumulate.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{ 

template<typename L, template<typename,typename> class F, typename Init>
struct accumulate_t
{
  typedef typename detail::accumulate_impl_t<L, F, Init>::type type;
};

template<typename L1, typename F, typename Init  >
struct accumulate
{
  typedef typename accumulate_t<L1, lambda<FAS_T_SIMPLIFY(F)>::template apply, Init >::type type;
};

}

#endif
