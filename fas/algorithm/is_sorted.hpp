//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_IS_SORTED_HPP
#define FAS_ALGORITHM_IS_SORTED_HPP

#include "detail/is_sorted.hpp"
#include <fas/integral/bool_.hpp>
#include <fas/integral/less.hpp>
#include <fas/mp/placeholders.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/algorithm/algomacro.hpp>
namespace fas{

template<typename L, typename F = less<_1, _2> >
struct is_sorted
{
  /*
#ifndef FAS_ALGORITHM_LAMBDA_CAST
  enum { value = detail::is_sorted_helper<L, FAS_T_SIMPLIFY(F) >::value  };
#else
  */
  enum { value = detail::is_sorted_helper_t<L, lambda<FAS_T_SIMPLIFY(F)>::template apply >::value  };
//#endif
  typedef bool_<value> type;
};

template<typename L, template <typename, typename> class F = less >
struct is_sorted_t
{
  enum { value = detail::is_sorted_helper_t<L, F >::value  };
  typedef bool_<value> type;
};

}


#endif
