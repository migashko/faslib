// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_HIERARCHY_FIELD_HPP
#define FAS_HIERARCHY_FIELD_HPP

//#include <fas/system/disable_warnings.hpp>

#include <fas/hierarchy/scatter_hierarchy.hpp>
#include <fas/type_list/type_at.hpp>
#include <fas/type_list/index_of.hpp>

namespace fas{

template<typename T, typename H>
T& field(H& h)
{
  typedef typename H::type_list_type type_list_type;
  typedef typename type_at< typename index_of<T, type_list_type >::type, type_list_type >::fulltail fulltail;
  return static_cast< detail::sh<fulltail> &>(h);
};

template<typename T, typename H>
const T& const_field(const H& h)
{
  typedef typename H::type_list_type type_list_type;
  typedef typename type_at< typename index_of<T, type_list_type >::type, type_list_type >::fulltail fulltail;
  return static_cast< const detail::sh<fulltail> &>(h);
};


/*
template<typename T, typename L>
T& field(scatter_hierarchy<L>& h)
{
  typedef typename type_at< typename index_of<T, L >::type, L >::fulltail fulltail;
  return static_cast< detail::sh<fulltail> &>(h);
};


template<typename T, typename L>
const T& field( const scatter_hierarchy<L>& h)
{
  typedef typename type_at< typename index_of<T, L >::type, L >::fulltail fulltail;
  return static_cast< const detail::sh<fulltail> &>(h);
};
*/

}

//#include <fas/system/enable_warnings.hpp>

#endif
