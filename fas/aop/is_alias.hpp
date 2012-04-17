// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_IS_ALIAS_HPP
#define FAS_AOP_IS_ALIAS_HPP

#include <fas/aop/metalist.hpp>
#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/aop/alias.hpp>


namespace fas{

template<typename T>
struct is_alias
{
 enum { value = is_has_metatype<T, metalist::alias>::value };
 typedef bool_< value > type;
};


template<typename Tg, typename TTg>
struct is_alias< alias<Tg, TTg> >
{
  enum { value = 1};
  typedef true_ type;
};

template<typename T>
struct is_forward
{
  enum { value = is_has_metatype<T, metalist::forward>::value };
  typedef bool_< value > type;
};


template<typename Tg, typename TTg>
struct is_forward< forward<Tg, TTg> >
{
  enum { value = 1};
  typedef true_ type;
};

template<typename T>
struct is_del
{
  enum { value = is_has_metatype<T, metalist::del>::value };
  typedef bool_< value > type;
};

template<typename Tg>
struct is_del< del<Tg> >
{
  enum { value = 1};
  typedef true_ type;
};


}

#endif
