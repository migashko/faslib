// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_P_HPP
#define FAS_MP_P_HPP

namespace fas{

template<typename T>
struct p{};

template<typename T>
struct unp { typedef T type; };

template< typename T >
struct unp< p<T> > { typedef T type; };

template<typename T>
struct is_p { enum {value = 0}; };

template<typename T>
struct is_p< p<T> > { enum {value = 1}; };

}

#endif
