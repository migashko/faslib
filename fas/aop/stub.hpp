//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_STUB_HPP
#define FAS_AOP_STUB_HPP

#include <fas/aop/metalist.hpp>

namespace fas {

/** Авайс-класс - заглушка. 
  * @param R - тип возвращаемого значения
  */
template<typename Tg, typename R = void>
class stub
{
public:
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef stub<Tg, R> advice_class;

  advice_class& get_advice() { return *this;}
  const advice_class& get_advice() const { return *this;}


  template<typename T>
  R operator()(T&) { return R(); }

  template<typename T, typename P1>
  R operator()(T&, P1) { return R(); }

  template<typename T, typename P1, typename P2>
  R operator()(T&, P1, P2) { return R(); }

  template<typename T, typename P1, typename P2, typename P3>
  R operator()(T&, P1, P2, P3) { return R(); }

  template<typename T, typename P1, typename P2, typename P3, typename P4>
  R operator()(T&, P1, P2, P3, P4) { return R(); }

  template<typename T, typename P1, typename P2, typename P3, typename P4, typename P5>
  R operator()(T&, P1, P2, P3, P4, P5) { return R(); }

};


}

#endif
