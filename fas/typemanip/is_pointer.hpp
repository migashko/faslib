//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_IS_POINTER_HPP
#define FAS_TYPEMANIP_IS_POINTER_HPP

#include <fas/integral/bool_.hpp>

namespace fas{

template<typename T>
struct is_pointer { enum { value = 0 }; };

template<typename T >
struct is_pointer< T* >{ enum { value = 0 }; };


}

#endif
