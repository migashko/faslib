//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_CHECK_RANGE_C_HPP
#define FAS_TYPE_LIST_CHECK_RANGE_C_HPP

#include <fas/type_list/detail/check_range.hpp>

namespace fas{

template<int I, typename L>
struct check_range_c
{
  typedef detail::check_range_helper<I, L> helper;
  typedef typename helper::error error;
  enum { value = helper::value};
};

// Включая длину 
template<int I, typename L>
struct check_range_c2
{
  typedef detail::check_range_helper2<I, L> helper;
  typedef typename helper::error error;
  enum { value = helper::value};
};

}


#endif
