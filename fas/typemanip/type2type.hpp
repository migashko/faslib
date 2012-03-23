// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_TYPE2TYPE_HPP
#define FAS_TYPEMANIP_TYPE2TYPE_HPP

namespace fas{

template<typename T>
struct type2type
{
  //typedef T value_type;
  typedef T original_type;
  //typedef type2type<T> type;
};

}

#endif
