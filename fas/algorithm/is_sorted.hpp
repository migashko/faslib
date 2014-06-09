//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_IS_SORTED_HPP
#define FAS_ALGORITHM_IS_SORTED_HPP

#include <fas/algorithm/detail/is_sorted.hpp>
#include <fas/algorithm/algomacro.hpp>
#include <fas/mp/placeholders.hpp>
#include <fas/mp/lambda.hpp>
#include <fas/integral/bool_.hpp>
#include <fas/integral/less.hpp>

namespace fas{

template<typename L, typename F = less<_,_> >
struct is_sorted
{
  enum { value = detail::is_sorted_impl_t<L, lambda<FAS_T_SIMPLIFY(F)>::template apply >::value  };
  typedef bool_<value> type;
};

template<typename L, template <typename, typename> class F = less >
struct is_sorted_t
{
  enum { value = detail::is_sorted_impl_t<L, F >::value  };
  typedef bool_<value> type;
};

}


#endif
