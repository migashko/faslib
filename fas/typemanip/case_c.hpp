//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_CASE_C_HPP
#define FAS_TYPEMANIP_CASE_C_HPP

namespace fas{

template<int C, typename T>
struct case_c
{
  enum { value = C };
  typedef T type;
};

}

#endif
