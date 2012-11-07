//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_IS_ALIAS_HPP
#define FAS_AOP_IS_ALIAS_HPP

#include <fas/aop/metalist.hpp>
#include <fas/aop/alias.hpp>
#include <fas/integral/bool_.hpp>
#include <fas/typemanip/is_has_metatype.hpp>

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

}

#endif
