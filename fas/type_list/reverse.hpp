//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//


#ifndef FAS_TYPE_LIST_REVERSE_HPP
#define FAS_TYPE_LIST_REVERSE_HPP

#include <fas/type_list/detail/reverse.hpp>

namespace fas{

template<typename T>
struct reverse
{
  typedef typename detail::reverse_helper<T>::type type;
};

}

#endif
