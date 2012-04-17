//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_IS_CONST_HPP
#define FAS_TYPEMANIP_IS_CONST_HPP


namespace fas{

template<typename T>
struct is_const { enum { value = 0 }; };

template<typename T>
struct is_const<const T> { enum { value = 1 }; };


}

#endif
