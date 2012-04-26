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

namespace fas{

template<typename T, typename H>
inline T& field(H& h)
{
  typedef typename H::type_list_type type_list_type;
  typedef typename type_at_c< index_of<T, type_list_type >::value, type_list_type >::fulltail fulltail;
  return static_cast< detail::sh<fulltail> &>(h);
};

template<typename T, typename H>
inline const T& field(const H& h)
{
  typedef typename H::type_list_type type_list_type;
  typedef typename type_at_c< index_of<T, type_list_type >::value, type_list_type >::fulltail fulltail;
  return static_cast< const detail::sh<fulltail> &>(h);
};

}

#endif
