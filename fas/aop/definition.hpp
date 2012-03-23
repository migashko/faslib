// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_DEFINITION_HPP
#define FAS_AOP_DEFINITION_HPP

#include <fas/aop/metalist.hpp>

namespace fas{

template<typename Tg, typename T>
class definition
{
public:
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef T advice_class;
};



}

#endif
