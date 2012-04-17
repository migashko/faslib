// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_F_HPP
#define FAS_MP_F_HPP

#include <fas/integral/int_.hpp>

namespace fas{

template<typename T>
struct f
{
  enum { value = T::value };
  typedef int_< value > type;

  /*template<typename TT>
  struct apply
  {
    enum { value = T::value };
    typedef int_< value > type;
  };*/
};


}

#endif
