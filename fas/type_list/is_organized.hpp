//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPE_LIST_IS_ORGANIZED_HPP
#define FAS_TYPE_LIST_IS_ORGANIZED_HPP

#include <fas/type_list/detail/is_organized.hpp>

namespace fas{

template<typename L>
struct is_organized
{
  enum { value = detail::is_organized_impl<L>::value};
};


}


#endif
