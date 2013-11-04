//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_FUNCTIONAL_MEMBER_SET_HPP
#define FAS_FUNCTIONAL_MEMBER_SET_HPP

namespace fas{

template<typename V, typename VT, VT V::* m>
struct member_set
{
  typedef VT value_type;
  VT& operator()(V& v) const
  {
    return v.*m;
  }
};

  
}

#endif

