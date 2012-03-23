//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_TYPE_LIST_SPLIT_C_HPP
#define FAS_IMPLEMENTATION_TYPE_LIST_SPLIT_C_HPP

#include "detail/split.hpp"
#include <fas/typemanip/pair.hpp>

namespace fas{


template<int I, typename L>
struct split_c
{
  typedef typename detail::split_helper<I, L>::left_list left_list;
  typedef typename detail::split_helper<I, L>::right_list right_list;
  typedef pair<left_list, right_list> type;
};


}

#endif
