//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_COUNT_HPP
#define FAS_ALGORITHM_COUNT_HPP

#include <fas/typemanip/same_type.hpp>
#include <fas/algorithm/count_if.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{

template<typename T, typename L>
struct count
  : count_if_t<L, lambda< same_type<T, _1> >::template apply > 
{};

}

#endif
