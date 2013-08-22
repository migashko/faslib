//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_IS_HAS_TYPENAME_HPP
#define FAS_TYPEMANIP_IS_HAS_TYPENAME_HPP

#include <fas/typemanip/detail/is_has_typename.hpp>

namespace fas{

template<typename T, typename D, template<typename> class F>
struct is_has_typename
{
  enum { value = detail::is_has_typename_impl<T, D, F>::value };
};


}

#endif
