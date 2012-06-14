//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_CLASS_HPP
#define FAS_AOP_ASPECT_CLASS_HPP

#include <fas/typemanip/empty_type.hpp>
#include <fas/aop/aspect_merge.hpp>
#include <fas/aop/private/aspect_hierarchy.hpp>

namespace fas{

template<typename A1, typename A2 = empty_type, typename A3 = empty_type, typename A4 = empty_type, typename A5 = empty_type >
class aspect_class
  : aspect_hierarchy< typename aspect_merge<A1, A2, A3, A4, A5>::type >
{
public:
  typedef typename aspect_merge<A1, A2, A3, A4, A5>::type aspect_type;
  typedef aspect_hierarchy< aspect_type > aspect;
  
  aspect& get_aspect() 
  {
    return static_cast<aspect&>(*this);
  }
  
  const aspect& get_aspect() const 
  {
    return static_cast<const aspect&>(*this);
  }
};

}

#endif
