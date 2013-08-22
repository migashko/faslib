//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_COUNT_IF_HPP
#define FAS_ALGORITHM_COUNT_IF_HPP

#include <fas/algorithm/detail/count_if.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/integral/int_.hpp>


namespace fas{

template<typename L, typename F >
struct count_if
{
  enum { value = detail::count_if_impl_t<L, lambda< FAS_T_SIMPLIFY(F) >::template apply >::value };
  typedef int_<value> type;
};

template<typename L, template<typename> class F >
struct count_if_t
{
  enum { value = detail::count_if_impl_t<L, F >::value };
  typedef int_<value> type;
};

}


#endif
