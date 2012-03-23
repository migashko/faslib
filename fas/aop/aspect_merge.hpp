// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_ASPECT_MERGE_HPP
#define FAS_AOP_ASPECT_ASPECT_MERGE_HPP

#include "detail/aspect_merge.hpp"

namespace fas{

template<typename A1, typename A2 >
struct aspect_merge
{
  typedef typename detail::aspect_merge_helper<A1,A2>::type type;
};

}

#endif

