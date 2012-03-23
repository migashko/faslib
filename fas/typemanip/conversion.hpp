// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_CONVERSION_HPP
#define FAS_TYPEMANIP_CONVERSION_HPP

#include "detail/conversion.hpp"
#include <fas/integral/bool_.hpp>

namespace fas{

template<typename L, typename R>
struct conversion
{
private:
  typedef detail::conversion_helper<L, R> helper;
public:
  enum { value = (sizeof( helper::test( helper::makeT() ) )==sizeof( typename helper::small_type)) };
  enum { some_type = 0};
  typedef bool_< value > type;
};

template<typename T>
struct conversion<T, T>
{
  enum { value = 1 };
  enum { some_type = 1};
  typedef bool_< value > type;
};


}

#endif
