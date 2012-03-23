//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_FIND_IF_HPP
#define FAS_ALGORITHM_FIND_IF_HPP

#include "detail/find_if.hpp"
#include <fas/mp/simplify.hpp>


namespace fas{

template<typename L, typename F >
struct find_if
{
#ifndef FAS_ALGORITHM_LAMBDA_CAST
  typedef detail::find_if_helper<L, FAS_T_SIMPLIFY(F) > helper;
#else
  typedef detail::find_if_helper_t<L, lambda<FAS_T_SIMPLIFY(F)>::template apply > helper;
#endif

  typedef typename helper::type type;
  typedef typename helper::tail tail;
  /*
#ifndef FAS_ALGORITHM_LAMBDA_CAST
  typedef typename detail::find_if_helper<L, FAS_T_SIMPLIFY(F) >::type type;
  typedef typename detail::find_if_helper<L, FAS_T_SIMPLIFY(F) >::tail tail;
#else
  typedef typename detail::find_if_helper_t<L, lambda<FAS_T_SIMPLIFY(F)>::template apply >::type type;
#endif
  */
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
