//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_VALUE_HPP
#define FAS_AOP_VALUE_HPP

#include <fas/aop/metalist.hpp>

namespace fas{

template<typename Tg, typename V >
class value
{
public:
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef V advice_class;

  value()
    :_value()
  {}

  advice_class& get_advice()
  {
    return _value;
  }

  const advice_class& get_advice() const
  {
    return _value;
  }

private:
   V _value;
};

}

#endif
