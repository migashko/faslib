//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_PH_NUM_HPP
#define FAS_MP_PH_NUM_HPP

#include <fas/mp/placeholders.hpp>

namespace fas{

template<typename F, int C = 0 >
struct ph_num { enum { value = 0, next = C}; };

template<int C>
struct ph_num<_, C> { enum { value = C + 1, next = C+1}; };

template<int C>
struct ph_num<_1, C> { enum { value = 1, next = C}; };

template<int C>
struct ph_num<_2, C> { enum { value = 2, next = C}; };

template<int C>
struct ph_num<_3, C> { enum { value = 3, next = C}; };

template<int C>
struct ph_num<_4, C> { enum { value = 4, next = C}; };

template<int C>
struct ph_num<_5, C> { enum { value = 5, next = C}; };

}

#endif
