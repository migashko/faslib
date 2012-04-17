//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_EMPTY_TYPE_HPP
#define FAS_TYPEMANIP_EMPTY_TYPE_HPP

#include <fas/typemanip/metalist.hpp>

namespace fas{

struct empty_type
{ 
  typedef metalist::empty_type metatype; 
};

}

#endif
