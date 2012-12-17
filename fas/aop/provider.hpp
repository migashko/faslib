//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_PROVIDER_HPP
#define FAS_AOP_PROVIDER_HPP

namespace fas{

template<typename M >
struct provider
{
  template<typename T>
  struct build
  {
    typedef typename fas::apply< typename M::type, T>::type type;
  };

  template<typename T>
  typename build<T>::type operator()(T& t) const
  {
    return typename build<T>::type(&t);
  }
};

}

#endif
