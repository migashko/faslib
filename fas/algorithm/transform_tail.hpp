//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ALGORITHM_TRANSFORM_TAIL_HPP
#define FAS_ALGORITHM_TRANSFORM_TAIL_HPP

#include <fas/algorithm/transform_tail_if.hpp>
#include <fas/algorithm/any.hpp>

namespace fas{


template<typename L, typename F>
struct transform_tail
{
  typedef typename transform_tail_if<L, F, any<_> >::type type;
};

template<typename L, template<typename> class F>
struct transform_tail_t
{
  typedef typename transform_tail_if_t<L, F, any >::type type;
};

}


#endif
