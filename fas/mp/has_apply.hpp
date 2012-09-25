//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_HAS_APPLY_HPP
#define FAS_MP_HAS_APPLY_HPP

#include <fas/typemanip/has_template.hpp>
#include <fas/typemanip/wrapper.hpp>

namespace fas{

FAS_HAS_TEMPLATE0(has_apply0, apply)
FAS_HAS_TEMPLATE1(has_apply1, apply)
FAS_HAS_TEMPLATE2(has_apply2, apply)
FAS_HAS_TEMPLATE3(has_apply3, apply)
FAS_HAS_TEMPLATE4(has_apply4, apply)
FAS_HAS_TEMPLATE5(has_apply5, apply)

template<typename T, int C = 1>
struct has_apply;

template<typename T, int C>
struct has_apply< w<T>, C >
{
  enum { value = 0 };
};

template<typename T>
struct has_apply<T, 0>
{
  enum { value = has_apply0<T>::value };
};

template<typename T>
struct has_apply<T, 1>
{
  enum { value = has_apply1<T>::value };
};

template<typename T>
struct has_apply<T, 2>
{
  enum { value = has_apply2<T>::value };
};

template<typename T>
struct has_apply<T, 3>
{
  enum { value = has_apply3<T>::value };
};

template<typename T>
struct has_apply<T, 4>
{
  enum { value = has_apply4<T>::value };
};

template<typename T>
struct has_apply<T, 5>
{
  enum { value = has_apply5<T>::value };
};

}

#endif

