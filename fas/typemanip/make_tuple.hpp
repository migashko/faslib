//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_MAKE_TUPLE_HPP
#define FAS_TYPEMANIP_MAKE_TUPLE_HPP

#include <fas/typemanip/tuple.hpp>
#include <fas/typemanip/empty_type.hpp>

namespace fas{

template<typename T1 = empty_type, typename T2 = empty_type, typename T3 = empty_type, typename T4 = empty_type, typename T5 = empty_type>
struct make_tuple
{
  typedef tuple<T1, T2, T3, T4, T5> type;
};


}

#endif
