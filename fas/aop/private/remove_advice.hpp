//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_PRIVATE_REMOVE_ADVICE_HPP
#define FAS_AOP_PRIVATE_REMOVE_ADVICE_HPP

#include <fas/aop/metalist.hpp>

namespace fas{

template<typename Tg>
struct remove_advice
{
  typedef metalist::remover metatype;
  typedef Tg tag;
};

}

#endif
