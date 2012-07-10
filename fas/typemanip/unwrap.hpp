//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_UNWRAP_HPP
#define FAS_TYPEMANIP_UNWRAP_HPP

#include <fas/typemanip/wrapper.hpp>

namespace fas{


template<typename T>
struct unwrap;

template<typename T>
struct unwrap< wrapper<T> >
{
  typedef T type;
};

}

#endif
