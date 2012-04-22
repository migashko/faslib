//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_W_HPP
#define FAS_MP_W_HPP

namespace fas{

template<typename T>
struct w{};

template<typename T>
struct unw { typedef T type; };

template< typename T >
struct unw< w<T> > { typedef T type; };

template<typename T>
struct is_w { enum {value = 0}; };

template<typename T>
struct is_w< w<T> > { enum {value = 1}; };


}

#endif
