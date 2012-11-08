//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ADVICE_HPP
#define FAS_AOP_ADVICE_HPP

#include <fas/aop/metalist.hpp>

namespace fas{

template<typename Tg, typename T>
class advice
  : T
{
public:
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef T advice_class;

  advice_class& get_advice() 
  { 
    return static_cast<advice_class&>(*this); 
  }
  
  const advice_class& get_advice() const 
  {
    return static_cast<const advice_class&>(*this); 
  }
};

}

#endif
