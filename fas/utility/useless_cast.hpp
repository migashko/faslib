//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2019
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_USELESS_CAST_HPP
#define FAS_USELESS_CAST_HPP

#include <fas/typemanip/same_type.hpp>

namespace fas{

namespace detail
{
  template<typename To, typename From>
  struct useless_cast_t
  {
    typedef To type;

    static type cast(const From& from)
    {
      return static_cast<To>(from);
    }
  };

  template<typename T>
  struct useless_cast_t<T, T>
  {
    typedef const T& type;

    static type cast(const T& from)
    {
      return from;
    }
  };
}

template<typename To, typename From>
inline typename detail::useless_cast_t<To, From>::type useless_cast(const From& from)
{
  return detail::useless_cast_t<To, From>::cast(from);
}

}

#endif
