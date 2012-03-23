//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_MAX_SIZEOF_HPP
#define FAS_TYPEMANIP_MAX_SIZEOF_HPP

#include <fas/typemanip/if_c.hpp>

namespace fas{

template<typename I1, typename I2>
struct max_sizeof
{
  typedef typename if_c< 
    (sizeof(I1::value) < sizeof(I2::value)),
    typename I2::value_type,
    typename I1::value_type
  >::type type;
};

}

#endif
