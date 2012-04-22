//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_A_HPP
#define FAS_MP_A_HPP

namespace fas{

template<typename T>
struct a{};

template<typename T>
struct una { typedef T type; };

template< typename T >
struct una< a<T> > { typedef T type; };

template<typename T>
struct is_a { enum {value = 0}; };

template<typename T>
struct is_a< a<T> > { enum {value = 1}; };

}

#endif
