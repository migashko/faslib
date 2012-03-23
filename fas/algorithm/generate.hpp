//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_GENERATE_HPP
#define FAS_ALGORITHM_GENERATE_HPP

#include <fas/type_list/empty_list.hpp>
#include <fas/algorithm/generate_c.hpp>

namespace fas{

template<typename I, typename G, typename P = empty_list >
struct generate
  : generate_c<I::value, G, P>
{
};

}

#endif
