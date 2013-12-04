//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_CLASS_HPP
#define FAS_AOP_ASPECT_CLASS_HPP

#include <fas/typemanip/empty_type.hpp>
#include <fas/aop/merge_aspect.hpp>
#include <fas/aop/private/aspect_hierarchy.hpp>

namespace fas{

template<typename A = empty_type >
class aspect_class
  : private aspect_hierarchy< A >
{
public:
  typedef A aspect_type;
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
