// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_AOP_ASPECT_CLASS_HPP
#define FAS_AOP_ASPECT_CLASS_HPP

#include <fas/typemanip/empty_type.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/is_aspect.hpp>
#include <fas/aop/aspect_merge.hpp>
#include <fas/aop/aspect_hierarchy.hpp>

namespace fas{

template< typename L, int >
struct aspect_helper_impl2
{
  typedef aspect< L > type;
};

template< typename T>
struct aspect_helper_impl2<T, false>
{
  typedef aspect< type_list<T> > type;
};


  
template< typename A, int >
struct aspect_helper_impl
{
  typedef A type;
};

template< typename A>
struct aspect_helper_impl<A, false>
  : aspect_helper_impl2< A, is_type_list<A>::value >
{};


template< typename A >
struct aspect_helper:
  aspect_helper_impl< A, is_aspect<A>::value >
{
  
};

template<>
struct aspect_helper< empty_type >
{
  typedef empty_type type;
};

template<>
struct aspect_helper< empty_list >
{
  typedef aspect< empty_list > type;
};

template< typename L >
struct aspect_helper< aspect< L > >
{
  typedef aspect< L > type;
};

template< typename L, typename R >
struct aspect_helper< type_list< L, R > >
{
  typedef aspect< type_list< L, R > > type;
};

template<typename A1, typename A2>
struct aspect_class_helper
{
  typedef typename aspect_merge<
    typename aspect_helper<A1>::type,
    typename aspect_helper<A2>::type
  >::type aspect_type;
  typedef aspect_hierarchy< aspect_type > aspect;
};
  
template<typename A1, typename A2 = empty_type >
class aspect_class
  : aspect_class_helper< A1, A2>::aspect 
  // aspect_hierarchy< typename aspect_merge< typename aspect_helper<A1>::type, typename aspect_helper<A2>::type >::type >
  // : private aspect_hierarchy< typename aspect_merge<A1, A2>::type >
  //: aspect_hierarchy< typename aspect_merge<A1, A2>::type >
{
public:
  typedef typename aspect_class_helper< A1, A2>::aspect_type aspect_type;
  typedef typename aspect_class_helper< A1, A2>::aspect aspect;
  /*
  typedef typename aspect_merge< typename aspect_helper<A1>::type, typename aspect_helper<A2>::type aspect_type;
  typedef aspect_hierarchy< aspect_type > aspect;
  */
  
  
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
  : aspect_hierarchy< typename aspect_helper< A >::type >
{
public:

  typedef typename aspect_helper< A >::type aspect_type;
  typedef aspect_hierarchy< aspect_type > aspect;

  /*
   * typedef A aspect_type;
  typedef aspect_hierarchy< aspect_type > aspect;
  */

  
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
