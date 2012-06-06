//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_FIELDX_HPP
#define FAS_SERIALIZATION_JSON_META_FIELDX_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/typemanip/remove_cvrp.hpp>
#include <fas/typemanip/const_if_const.hpp>

namespace fas{ namespace json{

template<typename VT, typename FG, typename FS,  typename J = empty_type>
struct fieldX
{
  typedef typename J::metatype metatype;
  typedef J target;
  typedef ser::_attr_ serializer_tag;
  typedef deser::_attr_ deserializer_tag;

  typedef typename remove_cvrp<VT>::type value_type;

  /*template<typename V>
  const VT& operator()(const V& v) const
  {
    return FG()(v);
  }*/

  template<typename V>
  VT& operator()(V& v) const
  {
    return FS()(v);
  }
};

template<typename VT, typename F, typename J >
struct fieldX<VT, F, J, empty_type>
{
  typedef typename J::metatype metatype;
  typedef J target;
  typedef ser::_attr_ serializer_tag;
  typedef deser::_attr_ deserializer_tag;

  typedef typename remove_cvrp<VT>::type value_type;

  /*
  template<typename V>
  const VT& operator()(const V& v) const
  {
    return F()(v);
  }*/

  template<typename V>
  /*typename if_c<
    is_const<V>::value,
    const VT,
    VT
  >::type& 
  */
  typename const_if_const<VT, V>::type&
  operator()(V& v) const
  {
    return F()(v);
  }
};

}}

#endif
