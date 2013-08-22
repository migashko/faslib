//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_SPLIT_C_HPP
#define FAS_TYPE_LIST_SPLIT_C_HPP

#include <fas/type_list/detail/split.hpp>
#include <fas/typemanip/pair.hpp>

namespace fas{


template<int I, typename L>
struct split_c
{
  typedef typename detail::split_impl<I, L>::left_list left_list;
  typedef typename detail::split_impl<I, L>::right_list right_list;
  typedef pair<left_list, right_list> type;
};


}

#endif
