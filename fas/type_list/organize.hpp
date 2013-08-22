//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_ORGANIZE_HPP
#define FAS_TYPE_LIST_ORGANIZE_HPP

#include <fas/type_list/detail/organize.hpp>

namespace fas{

template<typename L>
struct organize
{
  typedef typename detail::organize_impl<L>::type type;
};


}

#endif
