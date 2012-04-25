//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_REMOVE_ADVICE_HPP
#define FAS_AOP_REMOVE_ADVICE_HPP

#include <fas/aop/metalist.hpp>

namespace fas{

template<typename Tg>
struct remove_advice
{
  typedef metalist::remove_advice metatype;
  typedef Tg tag;
};

}

#endif
