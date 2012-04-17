//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_MAKE_PAIR_HPP
#define FAS_TYPEMANIP_MAKE_PAIR_HPP

#include <fas/typemanip/pair.hpp>

namespace fas{

template<typename T1, typename T2>
struct make_pair
{
  typedef pair<T1, T2> type;
};

}

#endif
