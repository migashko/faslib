//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_SELECT_HPP
#define FAS_ALGORITHM_SELECT_HPP

#include <fas/algorithm/detail/select.hpp>
#include <fas/algorithm/algomacro.hpp>

#include <fas/mp/lambda.hpp>

namespace fas{

template<typename L, typename F >
struct select
{
  typedef typename detail::select_impl_t<L, lambda< FAS_T_SIMPLIFY(F) >::template apply >::type type;
};

template<typename L, template<typename> class F >
struct select_t
{
  typedef typename detail::select_impl_t<L, F >::type type;
};

}

#endif
