//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//


#ifndef FAS_TYPEMANIP_IS_WRAPPER_HPP
#define FAS_TYPEMANIP_IS_WRAPPER_HPP

#include <fas/typemanip/wrapper.hpp>

namespace fas{

template<typename T>
struct is_wrapper
{
  enum { value = 0 };
};

template<typename T>
struct is_wrapper< wrapper<T> >
{
  enum { value = 1 };
};

}

#endif
