//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_PH_MAX_HPP
#define FAS_MP_PH_MAX_HPP

#include <fas/mp/detail/ph_max.hpp>

namespace fas{

template<typename F>
struct ph_max
{
  enum { value = detail::ph_max_impl<F>::value };
};

}

#endif
