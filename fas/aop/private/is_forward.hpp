//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_IS_FORWARD_HPP
#define FAS_AOP_IS_FORWARD_HPP

#include <fas/aop/metalist.hpp>
#include <fas/aop/forward.hpp>
#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/integral/bool_.hpp>

namespace fas{

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

}

#endif
