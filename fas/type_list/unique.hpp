//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_UNIQUE_HPP
#define FAS_TYPE_LIST_UNIQUE_HPP

#include <fas/type_list/detail/unique.hpp>

namespace fas{

template<typename L>
struct unique
{
  typedef typename detail::unique_helper<L>::type type;
};

}

#endif
