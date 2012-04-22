//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_PUSH_BACK_HPP
#define FAS_TYPE_LIST_PUSH_BACK_HPP

#include <fas/type_list/merge.hpp>

namespace fas{

template<typename T, typename L>
struct push_back
{
  typedef typename merge< L, T >::type type;
};


}

#endif
