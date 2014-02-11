//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_UNIQUE_IF_HPP
#define FAS_ALGORITHM_UNIQUE_IF_HPP

#include <fas/algorithm/detail/unique_if.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/placeholders.hpp>
#include <fas/typemanip/same_type.hpp>
#include <fas/integral/less.hpp>

namespace fas{

template<typename L, typename F = same_type< _1,  _2 > >
struct unique_if
{
  typedef typename detail::unique_if_impl_t< L, lambda_r< FAS_T_SIMPLIFY(F) , 2 >::template apply >::type type;
};

template<typename L, template<typename, typename> class F >
struct unique_if_t
{
  typedef typename detail::unique_if_impl_t< L, F >::type type;
};


}


#endif
