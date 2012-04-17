//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//


#ifndef FAS_TYPEMANIP_TYPE2TYPE_HPP
#define FAS_TYPEMANIP_TYPE2TYPE_HPP

namespace fas{

template<typename T>
struct type2type
{
  typedef T original_type;
};

}

#endif
