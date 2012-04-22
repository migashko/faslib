//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_FIND_IF_HPP
#define FAS_ALGORITHM_FIND_IF_HPP

#include <fas/algorithm/detail/find_if.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{

template<typename L, typename F >
struct find_if
{
  typedef detail::find_if_helper_t<L, lambda<FAS_T_SIMPLIFY(F)>::template apply > helper;
  typedef typename helper::type type;
  typedef typename helper::tail tail;
};

template<typename L, template<typename> class F >
struct find_if_t
{
  typedef detail::find_if_helper_t<L, F > helper;
  typedef typename helper::type type;
  typedef typename helper::tail tail;
};

}


#endif
