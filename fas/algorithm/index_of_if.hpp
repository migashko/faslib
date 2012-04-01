//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_INDEX_OF_IF_HPP
#define FAS_ALGORITHM_INDEX_OF_IF_HPP

#include "detail/index_of_if.hpp"
#include <fas/integral/int_.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/algorithm/algomacro.hpp>


namespace fas{

template<typename L, typename F >
struct index_of_if
{
  /*
#ifndef FAS_ALGORITHM_LAMBDA_CAST
  enum { value = detail::index_of_if_helper<L, FAS_T_SIMPLIFY(F) >::value  };
#else
  */
  enum { value = detail::index_of_if_helper_t<L, lambda< FAS_T_SIMPLIFY(F) >::template apply >::value  };
//#endif
  typedef int_<value> type;
};

template<typename L, template<typename> class F >
struct index_of_if_t
{
  enum { value = detail::index_of_if_helper_t<L, F >::value  };
  typedef int_<value> type;
};

}

#endif
