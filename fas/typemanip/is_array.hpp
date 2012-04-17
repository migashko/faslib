//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_IS_ARRAY_HPP
#define FAS_TYPEMANIP_IS_ARRAY_HPP

#include <fas/integral/bool_.hpp>

namespace fas
{

template<typename T>
struct is_array { enum { value = 0 }; };

template<typename T, int N >
struct is_array< T[N] > { enum { value = 1  }; };

template<typename T >
struct is_array< T[] > { enum { value = 1  }; };

}

#endif
