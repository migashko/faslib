//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_CONST_IF_C_HPP
#define FAS_TYPEMANIP_CONST_IF_C_HPP

namespace fas{
  
template<typename T, int C>
struct const_if_c
{
  enum { value = 1};
  typedef const T type;
};

template<typename T>
struct const_if_c<T, false>
{
  enum { value = 0};
  typedef T type;
};

}

#endif
