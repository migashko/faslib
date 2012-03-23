//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_SELECT_HPP
#define FAS_ALGORITHM_SELECT_HPP

#include "detail/select.hpp"
#include <fas/algorithm/algomacro.hpp>
#include <fas/integral/not_.hpp>

namespace fas{

template<typename L, typename F >
struct select
{
#ifndef FAS_ALGORITHM_LAMBDA_CAST
  typedef typename detail::select_helper<L, FAS_T_SIMPLIFY(F) >::type type;
#else
  typedef typename detail::select_helper_t<L, lambda< FAS_T_SIMPLIFY(F) >::template apply >::type type;
#endif
};

template<typename L, template<typename> class F >
struct select_t
{
  typedef typename detail::select_helper_t<L, F >::type type;
};

}

#endif
