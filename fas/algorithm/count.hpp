//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_COUNT_HPP
#define FAS_ALGORITHM_COUNT_HPP

#include <fas/typemanip/some_type.hpp>
#include <fas/algorithm/count_if.hpp>
#include <fas/mp/lambda.hpp>

namespace fas{

  
  /*
#ifndef FAS_ALGORITHM_LAMBDA_CAST
template<typename T, typename L>
struct count: count_if<L, some_type<T, _1> > { };
#else
*/
template<typename T, typename L>
struct count: count_if_t<L, lambda< some_type<T, _1> >::template apply > { };
/*
#endif
*/

}


#endif
