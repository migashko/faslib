// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_IS_POINTER_HPP
#define FAS_TYPEMANIP_IS_POINTER_HPP

#include <fas/integral/bool_.hpp>

namespace fas{

template<typename T>
struct is_pointer: false_ { typedef false_ type; };

template<typename T >
struct is_pointer< T* >: true_ { typedef true_ type; };


}

#endif
