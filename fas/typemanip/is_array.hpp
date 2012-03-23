// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_IS_ARRAY_HPP
#define FAS_TYPEMANIP_IS_ARRAY_HPP

#include <fas/integral/bool_.hpp>
namespace fas{

template<typename T>
struct is_array: false_ { typedef false_ type; };

template<typename T, int N >
struct is_array< T[N] >: true_ { typedef true_ type; };

template<typename T >
struct is_array< T[] >: true_ { typedef true_ type; };

}

#endif
