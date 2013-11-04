//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_FUNCTIONAL_MEMBER_GET_HPP
#define FAS_FUNCTIONAL_MEMBER_GET_HPP

namespace fas{

template<typename V, typename VT, VT V::* m>
struct member_get
{
  typedef VT value_type;
  const VT& operator()(const V& v) const
  {
    return v.*m;
  }
};

}

#endif
