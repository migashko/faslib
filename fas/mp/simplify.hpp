//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_SIMPLIFY_HPP
#define FAS_MP_SIMPLIFY_HPP

#include <fas/mp/detail/simplify.hpp>

namespace fas{

template<typename F>
struct simplify
{
  typedef typename detail::simplify_impl<F>::type type;
};


}

#endif
