// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_BIND_HPP
#define FAS_MP_BIND_HPP

#include "detail/bind.hpp"

namespace fas{

template<typename PE, typename L = empty_list >
struct bind
{
  typedef typename detail::bind_helper<PE, L >::type type;
};
 
template< template<typename, typename> class F, typename P>
struct bind1st
{
  template<typename T>
  struct apply: F<P, T> {};
};

template< template<typename, typename> class F, typename P>
struct bind2nd
{
  template<typename T>
  struct apply: F<T, P> {};
};

}

#endif

