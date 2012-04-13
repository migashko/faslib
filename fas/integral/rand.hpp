//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_RAND_HPP
#define FAS_INTEGRAL_RAND_HPP


#include <fas/integral/int_.hpp>
#include <fas/integral/integral_c.hpp>
#include <fas/typemanip/max_sizeof.hpp>

namespace fas{

template<typename R = int_<0x50000> >
struct rand
{
  typedef unsigned long rand_type;
  typedef typename R::value_type value_type;
  typedef integral_c< 
    value_type,
    static_cast<value_type>( ( static_cast<rand_type>(R::value) * 0x43fd43fd + 0xc39ec3) & 0xffffff)
  > type;

  enum { value = type::value };

  typedef integral_c< typename R::value_type, R::value> initial;
};

}



#endif
