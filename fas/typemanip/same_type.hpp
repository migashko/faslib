//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_SAME_TYPE_HPP
#define FAS_TYPEMANIP_SAME_TYPE_HPP

namespace fas{

template<typename L, typename R>
struct same_type
{
  enum { value = 0 };
};

template<typename T>
struct same_type<T, T>
{
  enum { value = 1 };
};

}

#endif
