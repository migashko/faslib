//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_UNIQUE_IF_HPP
#define FAS_ALGORITHM_UNIQUE_IF_HPP

#include "detail/unique_if.hpp"
#include <fas/mp/simplify.hpp>
#include <fas/integral/less.hpp>
#include <fas/mp/placeholders.hpp>
#include <fas/mp/a.hpp>
#include <fas/mp/p.hpp>
#include <fas/typemanip/some_type.hpp>

namespace fas{

template<typename L, typename F = some_type< _1,  _2 >/*a< some_type< _1,  p<_1> > >*/ >
struct unique_if
{
  /*
#ifndef FAS_ALGORITHM_LAMBDA_CAST
  typedef typename detail::unique_if_helper<L, FAS_T_SIMPLIFY(F) >::type type;
#else
  */
  typedef typename detail::unique_if_helper_t< L, lambda/*_r*/< FAS_T_SIMPLIFY(F) , 2 >::template apply >::type type;
  /*
#endif
  */
};

template<typename L, template<typename, typename> class F >
struct unique_if_t
{
  typedef typename detail::unique_if_helper_t< L, F >::type type;
};


}


#endif
