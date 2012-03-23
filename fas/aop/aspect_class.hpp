// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_CLASS_HPP
#define FAS_AOP_ASPECT_CLASS_HPP

#include <fas/typemanip/empty_type.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/aspect_merge.hpp>
#include <fas/aop/aspect_hierarchy.hpp>

namespace fas{

template<typename A1, typename A2 = empty_type >
class aspect_class
  : aspect_hierarchy< typename aspect_merge<A1, A2>::type >
  // : private aspect_hierarchy< typename aspect_merge<A1, A2>::type >
  //: aspect_hierarchy< typename aspect_merge<A1, A2>::type >
{
public:
  typedef typename aspect_merge<A1, A2>::type aspect_type;
  typedef aspect_hierarchy< aspect_type > aspect;
  
  
  aspect& get_aspect() { return static_cast<aspect&>(*this);}
  const aspect& get_aspect() const { return static_cast<const aspect&>(*this);}
  
  /*
  
  aspect& get_aspect() { return _aspect;}
  const aspect& get_aspect() const { return _aspect;}
private:
  aspect _aspect;
  */
};

template<typename A>
class aspect_class<A, empty_type>
  : aspect_hierarchy< A >
{
public:
  typedef A aspect_type;
  typedef aspect_hierarchy< aspect_type > aspect;

  
  aspect& get_aspect() { return static_cast<aspect&>(*this);}
  const aspect& get_aspect() const { return static_cast<const aspect&>(*this);}
  
  /*
  aspect& get_aspect() { return _aspect;}
  const aspect& get_aspect() const { return _aspect;}
private:
  aspect _aspect;
  */
  
};

}

#endif
