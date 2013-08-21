//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_MERGE_ASPECT_HPP
#define FAS_AOP_ASPECT_MERGE_ASPECT_HPP

#include <fas/aop/detail/merge_aspect.hpp>
#include <fas/typemanip/empty_type.hpp>

namespace fas{

template<typename A1, typename A2, typename A3 = empty_type, typename A4 = empty_type, typename A5 = empty_type>
struct merge_aspect
{
  typedef typename detail::merge_aspect<A1,A2,A3,A4,A5>::type type;
};

}

#endif

