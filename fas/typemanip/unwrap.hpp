//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_UNWRAP_HPP
#define FAS_TYPEMANIP_UNWRAP_HPP

#include "detail/unwrap.hpp"

#include <fas/typemanip/wrapper.hpp>

namespace fas{

template<typename T>
struct unwrap
{
  typedef typename detail::unwrap_helper<T>::type type;
};

template<typename T>
struct unwrap< wrapper<T> >
{
  typedef T type;
};



}

#endif
