//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_SORT_HPP
#define FAS_ALGORITHM_SORT_HPP

#include "detail/sort.hpp"
#include <fas/mp/simplify.hpp>
#include <fas/integral/less.hpp>
#include <fas/mp/placeholders.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{

template<typename L, typename F = less<_1, _2> >
struct sort
{
/*#ifndef FAS_ALGORITHM_LAMBDA_CAST
  typedef typename detail::sort_helper<L, FAS_T_SIMPLIFY(F) >::type type;
#else*/
  typedef typename detail::sort_helper_t<L, lambda_r<FAS_T_SIMPLIFY(F), 2>::template apply >::type type;
//#endif
};

template<typename L, template <typename, typename> class F = less >
struct sort_t
{
  typedef typename detail::sort_helper_t<L, F >::type type;
};

}


#endif
