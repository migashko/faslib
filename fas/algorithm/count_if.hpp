//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_COUNT_IF_HPP
#define FAS_ALGORITHM_COUNT_IF_HPP

#include "detail/count_if.hpp"
#include <fas/integral/int_.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/lambda.hpp>


namespace fas{

template<typename L, typename F >
struct count_if
{
  /*
#ifndef FAS_ALGORITHM_LAMBDA_CAST
  enum { value = detail::count_if_helper<L, FAS_T_SIMPLIFY(F) >::value };
#else*/
  enum { value = detail::count_if_helper_t<L, lambda<FAS_T_SIMPLIFY(F)>::template apply >::value };
//#endif
  typedef int_<value> type;
};

template<typename L, template<typename> class F >
struct count_if_t
{
  enum { value = detail::count_if_helper_t<L, F >::value };
  typedef int_<value> type;
};

}


#endif
