// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_INTEGRAL_INTEGRAL2TYPE_HPP
#define FAS_INTEGRAL_INTEGRAL2TYPE_HPP

namespace fas{

template<typename I, I i>
struct integral2type
{
  typedef I value_type;
  enum { value = i};
  //static const I value = i;
};

}

#endif
