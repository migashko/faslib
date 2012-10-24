//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_VALUE_ADVICE_HPP
#define FAS_AOP_VALUE_ADVICE_HPP

#include <fas/aop/metalist.hpp>

namespace fas{

template<typename Tg, typename T>
class value_advice
{
public:
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef T advice_class;

  value_advice():_value(){}
  advice_class& get_advice() { return _value;}
  const advice_class& get_advice() const { return _value;}

private:
   T _value;
};

}

#endif
