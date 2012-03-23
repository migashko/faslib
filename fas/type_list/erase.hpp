//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_TYPE_LIST_ERASE_HPP
#define FAS_IMPLEMENTATION_TYPE_LIST_ERASE_HPP

#include <fas/type_list/erase_c.hpp>

namespace fas{


template<typename I, typename L>
struct erase
  : erase_c<I::value, L>
{
  
};

}

#endif
