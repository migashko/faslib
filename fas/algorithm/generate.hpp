//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_GENERATE_HPP
#define FAS_ALGORITHM_GENERATE_HPP

#include <fas/type_list/empty_list.hpp>
#include <fas/algorithm/generate_c.hpp>

namespace fas{

template<typename I, typename G>
struct generate
  : generate_c< I::value, G>
{
};

}

#endif
