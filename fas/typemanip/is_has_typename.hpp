// ага
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_IS_HAS_TYPENAME_HPP
#define FAS_TYPEMANIP_IS_HAS_TYPENAME_HPP

#include "detail/is_has_typename.hpp"
#include <fas/integral/bool_.hpp>

namespace fas{

template<typename T, typename D, template<typename> class F>
struct is_has_typename
{
  enum { value = detail::is_has_typename_helper<T, D, F>::value };
  // Ахтунг! не метафункция
  typedef bool_< value > type;
};


}

#endif
