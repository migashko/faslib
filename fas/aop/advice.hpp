// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ADVICE_HPP
#define FAS_AOP_ADVICE_HPP

#include <fas/system/disable_warnings.hpp>

#include <fas/aop/metalist.hpp>

namespace fas{

template<typename Tg, typename T>
class value_advice
  // : public T
{
public:
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef T advice_class;

  /*
  advice_class& get_advice() { return static_cast<advice_class&>(*this); }
  const advice_class& get_advice() const { return static_cast<const advice_class&>(*this); }
  */
  advice_class& get_advice() { return _value;}
  const advice_class& get_advice() const { return _value;}
  
private:
   T _value;
};

template<typename Tg, typename T>
class advice
  : /*public */T
{
public:
  typedef metalist::advice metatype;
  typedef Tg tag;
  typedef T advice_class;

  
  advice_class& get_advice() { return static_cast<advice_class&>(*this); }
  const advice_class& get_advice() const { return static_cast<const advice_class&>(*this); }
  
  /*
  advice_class& get_advice() { return _value;}
  const advice_class& get_advice() const { return _value;}
  */
  
private:
  // T _value;
};


}

#include <fas/system/enable_warnings.hpp>

#endif
