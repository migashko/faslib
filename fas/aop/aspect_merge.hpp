//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_ASPECT_MERGE_HPP
#define FAS_AOP_ASPECT_ASPECT_MERGE_HPP

#include <fas/aop/detail/aspect_merge.hpp>

namespace fas{

template<typename A1, typename A2, typename A3 = empty_type, typename A4 = empty_type, typename A5 = empty_type>
struct aspect_merge
{
  typedef typename detail::aspect_merge_helper<A1,A2,A3,A4,A5>::type type;
};

}

#endif

