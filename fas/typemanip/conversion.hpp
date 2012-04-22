//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_CONVERSION_HPP
#define FAS_TYPEMANIP_CONVERSION_HPP

#include <fas/typemanip/detail/conversion.hpp>

namespace fas{

template<typename L, typename R>
struct conversion
{
private:
  typedef detail::conversion_helper<L, R> helper;
public:
  enum { value = (sizeof( helper::test( helper::makeT() ) )==sizeof( typename helper::small_type)) };
  enum { some_type = 0};
};

template<typename T>
struct conversion<T, T>
{
  enum { value = 1 };
  enum { some_type = 1};
};

}

#endif
