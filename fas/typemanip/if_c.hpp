//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_IF_C_HPP
#define FAS_TYPEMANIP_IF_C_HPP

namespace fas{
  
template<int C, typename T1, typename T2>
struct if_c
{
  enum { value = 1};
  typedef T1 type;
};

template< typename T1, typename T2>
struct if_c<false, T1, T2>
{
  enum { value = 0};
  typedef T2 type;
};

}

#endif
