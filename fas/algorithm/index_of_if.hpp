//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_INDEX_OF_IF_HPP
#define FAS_ALGORITHM_INDEX_OF_IF_HPP

#include <fas/algorithm/detail/index_of_if.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/integral/int_.hpp>

namespace fas{

template<typename L, typename F >
struct index_of_if
{
  enum { value = detail::index_of_if_impl_t<L, lambda< FAS_T_SIMPLIFY(F) >::template apply >::value  };
  typedef int_<value> type;
};

template<typename L, template<typename> class F >
struct index_of_if_t
{
  enum { value = detail::index_of_if_impl_t<L, F >::value  };
  typedef int_<value> type;
};

}

#endif
