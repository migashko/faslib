//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_CONST_IF_CONST_HPP
#define FAS_TYPEMANIP_CONST_IF_CONST_HPP

#include <fas/typemanip/const_if_c.hpp>
#include <fas/typemanip/is_const.hpp>

namespace fas{
  
template<typename T, typename TC>
struct const_if_const 
  : const_if_c< T, is_const<TC>::value >
{
};

}

#endif
