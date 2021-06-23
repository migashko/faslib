//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//


#ifndef FAS_INTEGRAL_GREATER_HPP
#define FAS_INTEGRAL_GREATER_HPP

#include <fas/integral/bool_.hpp>
#include <fas/typemanip/max_sizeof.hpp>

namespace fas{

template<typename A, typename B>
struct greater
{
  typedef typename max_sizeof< typename A::value_type, typename B::value_type >::type value_type;
  enum { value = ( static_cast<value_type>(A::value) - static_cast<value_type>(B::value) > 0)};
  typedef bool_<value> type;
};

}

#endif
