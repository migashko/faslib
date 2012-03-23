//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_FACTORIAL_HPP
#define FAS_INTEGRAL_FACTORIAL_HPP

#include <fas/integral/integral_c.hpp>
#include "detail/factorial.hpp"

namespace fas{

template<typename I>
struct factorial
{
	enum { initial = I::value};
	enum { less_zero = I::value < 0};
  typedef integral_c<
    typename I::value_type,
	detail::factorial_helper<initial, less_zero >::value
	// так VS не распознает
    //detail::factorial_helper<I::value, ((I::value < 0)) >::value
  > type;
  enum { value = type::value };
};

}

#endif
