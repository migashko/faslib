//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_SWITCH__HPP
#define FAS_TYPEMANIP_SWITCH__HPP

#include <fas/typemanip/detail/switch_.hpp>
#include <fas/type_list/normalize.hpp>

namespace fas{

template<typename L>
struct switch_
{
  typedef typename detail::switch_helper< typename normalize<L>::type >::type type;
};

}

#endif
