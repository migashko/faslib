//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_ARG_HPP
#define FAS_MP_ARG_HPP

namespace fas{

template<typename T>
struct arg {};

template<typename T>
struct arg_extract { typedef T type; };

template< typename T >
struct arg_extract< arg<T> > { typedef T type; };

template<typename T>
struct is_arg { enum {value = 0}; };

template<typename T>
struct is_arg< arg<T> > { enum {value = 1}; };

}

#endif
