// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_IS_ASPECT_HPP
#define FAS_AOP_IS_ASPECT_HPP

#include <fas/aop/metalist.hpp>
#include <fas/aop/stub.hpp>
#include <fas/aop/aspect.hpp>

#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/integral/bool_.hpp>


namespace fas{

template<typename T>
struct is_aspect
  : is_has_metatype<T, metalist::aspect>
{
};


template<typename L>
struct is_aspect< aspect<L> >
{
  enum { value = 1};
  typedef true_ type;
};


}

#endif
