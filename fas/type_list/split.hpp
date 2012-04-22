//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_SPLIT_HPP
#define FAS_TYPE_LIST_SPLIT_HPP

#include <fas/type_list/split_c.hpp>

namespace fas{

template<typename I, typename L>
struct split
  :split_c<I::value, L>
{
};

}

#endif
