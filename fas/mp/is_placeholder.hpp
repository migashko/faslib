//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_IS_PLACEHOLDERS_HPP
#define FAS_MP_IS_PLACEHOLDERS_HPP

#include <fas/mp/placeholders.hpp>

namespace fas{

template<typename T>
struct is_placeholder { enum { value = 0}; };

template<>
struct is_placeholder<_> { enum { value = 1}; };

template<>
struct is_placeholder<_1> { enum { value = 1}; };

template<>
struct is_placeholder<_2> { enum { value = 1}; };

template<>
struct is_placeholder<_3> { enum { value = 1}; };

template<>
struct is_placeholder<_4> { enum { value = 1}; };

template<>
struct is_placeholder<_5> { enum { value = 1}; };

template<int I>
struct is_placeholder< placeholder<I> > { enum { value = 1}; };

}

#endif
