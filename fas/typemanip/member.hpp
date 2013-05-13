//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_ACCESS_MEMBER_HPP
#define FAS_ACCESS_MEMBER_HPP

#include <fas/typemanip/const_if_const.hpp>

namespace fas{

template<typename V, typename VT, VT V::* m>
struct member
{
  template<typename VV>
  typename const_if_const<VT, VV>::type& operator()(VV& v) const
  {
    return v.*m;
  }
};

}

#endif
