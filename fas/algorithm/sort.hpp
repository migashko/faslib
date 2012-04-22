//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_SORT_HPP
#define FAS_ALGORITHM_SORT_HPP

#include <fas/algorithm/detail/sort.hpp>
#include <fas/algorithm/algomacro.hpp>

#include <fas/mp/simplify.hpp>
#include <fas/mp/placeholders.hpp>
#include <fas/mp/lambda.hpp>

#include <fas/integral/less.hpp>

namespace fas{

template<typename L, typename F = less<_1, _2> >
struct sort
{
  typedef typename detail::sort_helper_t<L, lambda_r<FAS_T_SIMPLIFY(F), 2>::template apply >::type type;
};

template<typename L, template <typename, typename> class F = less >
struct sort_t
{
  typedef typename detail::sort_helper_t<L, F >::type type;
};

}


#endif
