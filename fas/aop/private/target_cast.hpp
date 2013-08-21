//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_TARGET_CAST_HPP
#define FAS_AOP_TARGET_CAST_HPP

namespace fas{

template<typename AL>
struct target_cast
{
  typedef typename AL::target type;
};

}

#endif
