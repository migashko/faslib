//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ADVICE_CAST_HPP
#define FAS_AOP_ADVICE_CAST_HPP

#include <fas/aop/private/find_advice.hpp>

namespace fas {

template<typename Tg, typename A>
struct advice_cast
{
  typedef typename find_advice< Tg, typename A::common_list >::type::advice_class type;
};

}

#endif
