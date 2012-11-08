//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_TYPE_ADVICE_HPP
#define FAS_AOP_TYPE_ADVICE_HPP

#include <fas/aop/metalist.hpp>
#include <fas/aop/private/is_remover.hpp>
#include <fas/integral/bool_.hpp>

namespace fas{

template<typename Tg, typename T>
class type_advice
{
public:
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef T advice_class;
};


}

#endif
