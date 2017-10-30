//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_HIERARCHY_FIELD_IF_HPP
#define FAS_HIERARCHY_FIELD_IF_HPP

#include <fas/hierarchy/scatter_hierarchy.hpp>

#include <fas/type_list/type_at.hpp>
#include <fas/algorithm/index_of_if.hpp>
#include <fas/algorithm/find_if.hpp>

namespace fas{

template<typename F>
struct field_if
{
  template<typename H>
  static inline
  typename find_if< typename H::hierarchy_list, F>::type&
  get(H& h)
  {
    typedef typename H::hierarchy_list hierarchy_list;

    typedef typename type_at<
      typename index_of_if<hierarchy_list, F>::type,
      hierarchy_list
    >::fulltail fulltail;

    return static_cast< detail::sh<fulltail> &>(h);
  }

  template<typename H>
  static inline const
  typename find_if< typename H::hierarchy_list, F>::type&
  get_const(const H& h)
  {
    typedef typename H::hierarchy_list hierarchy_list;

    typedef typename type_at<
      typename index_of_if<hierarchy_list, F>::type,
      hierarchy_list
    >::fulltail fulltail;

    return static_cast< const detail::sh<fulltail> &>(h);
  }
};

template< template<typename> class F >
struct field_if_t
{
  template<typename H>
  static inline
  typename find_if_t< typename H::hierarchy_list, F>::type&
  get(H& h)
  {
    typedef typename H::hierarchy_list hierarchy_list;
    typedef typename type_at<
      typename index_of_if_t<hierarchy_list, F>::type,
      hierarchy_list
    >::fulltail fulltail;
    return static_cast< detail::sh<fulltail> &>(h);
  }

  template<typename H>
  static inline
  const typename find_if_t< typename H::hierarchy_list, F>::type&
  get_const(const H& h)
  {
    typedef typename H::hierarchy_list hierarchy_list;
    typedef typename type_at<
      typename index_of_if_t<hierarchy_list, F>::type,
      hierarchy_list
    >::fulltail fulltail;
    return static_cast< const detail::sh<fulltail> &>(h);
  }
};

}

#endif
