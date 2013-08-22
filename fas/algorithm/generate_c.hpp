//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_GENERATE_C_HPP
#define FAS_ALGORITHM_GENERATE_C_HPP

#include <fas/algorithm/detail/generate.hpp>
#include <fas/type_list/empty_list.hpp>

namespace fas{

template<int I, typename G>
struct generate_c
{
  typedef typename detail::generate_impl<I, G>::type type;
};

}

#endif
