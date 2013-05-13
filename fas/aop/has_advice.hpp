//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_HAS_ADVICE_HPP
#define FAS_AOP_HAS_ADVICE_HPP

#include <fas/aop/detail/has_advice.hpp>

namespace fas {

template<typename Tg, typename T>
struct has_advice
{
  typedef typename detail::has_advice_aspect<Tg, typename T::aspect>::type type;
};

}

#endif
