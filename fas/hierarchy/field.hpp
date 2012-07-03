//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2006, 2007, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_HIERARCHY_FIELD_HPP
#define FAS_HIERARCHY_FIELD_HPP

#include <fas/hierarchy/scatter_hierarchy.hpp>
#include <fas/type_list/type_at_c.hpp>
#include <fas/type_list/index_of.hpp>
#include <fas/type_list/length.hpp>

namespace fas {


template<typename T>
struct field
{
  template<typename H>
  inline static T& get(H& h)
  {
    typedef typename H::hierarchy_list hierarchy_list;
    typedef typename type_at_c< index_of<T, hierarchy_list >::value, hierarchy_list >::fulltail fulltail;
    return static_cast<T&>( static_cast< detail::sh<fulltail> &>(h) );
  }
  
  template<typename H>
  inline static const T& get_const(const H& h)
  {
    typedef typename H::hierarchy_list hierarchy_list;
    typedef typename type_at_c< index_of<T, hierarchy_list >::value, hierarchy_list >::fulltail fulltail;
    return static_cast<const T&>( static_cast< const detail::sh<fulltail> &>(h) );
  };

};





}

#endif
