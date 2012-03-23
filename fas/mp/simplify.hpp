// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_SIMPLIFY_HPP
#define FAS_MP_SIMPLIFY_HPP

#include "detail/simplify.hpp"

namespace fas{

template<typename F>
struct simplify
{
  //typedef F type;
  typedef typename detail::simplify_helper<F>::type type;

};


}

#endif
