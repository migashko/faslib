//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_MP_BIND2ND_HPP
#define FAS_MP_BIND2ND_HPP

namespace fas{

template< template<typename, typename> class F, typename P>
struct bind2nd
{
  template<typename T>
  struct apply: F<T, P> {};
};

}

#endif

