//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_SOME_TYPE_HPP
#define FAS_TYPEMANIP_SOME_TYPE_HPP

namespace fas{

template<typename L, typename R>
struct some_type
{
  enum { value = 0 };
};

template<typename T>
struct some_type<T, T>
{
  enum { value = 1 };
};

}

#endif
