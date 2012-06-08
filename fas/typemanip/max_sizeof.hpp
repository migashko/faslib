//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2012
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
    ( sizeof(I1) < sizeof(I2) ),
    I2,
    I1
  >::type type;
};

}

#endif
