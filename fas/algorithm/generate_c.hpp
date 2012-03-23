//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_GENERATE_C_HPP
#define FAS_ALGORITHM_GENERATE_C_HPP

#include "detail/generate.hpp"
#include <fas/type_list/empty_list.hpp>

namespace fas{

template<int I, typename G, typename P = empty_list >
struct generate_c
{
  typedef typename detail::generate_helper<I, G, P>::type type;
};

}

#endif
