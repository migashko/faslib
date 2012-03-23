//
// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_IMPLEMENTATION_TYPE_LIST_PUSH_FRONT_HPP
#define FAS_IMPLEMENTATION_TYPE_LIST_PUSH_FRONT_HPP


//#include <fas/type_list/normalize.hpp>
#include <fas/type_list/merge.hpp>

namespace fas{

template<typename T, typename L>
struct push_front
{
  typedef typename merge< T, L>::type type;
};

}

#endif
