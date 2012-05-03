//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_ATTR_HPP
#define FAS_SERIALIZATION_JSON_META_ATTR_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/typemanip/remove_cvrp.hpp>

namespace fas{ namespace json{

template<typename V, typename VT, VT V::* m, typename J>
struct attr
{
  typedef typename J::metatype metatype;
  typedef J target;
  typedef ser::_attr_ serializer_tag;
  typedef deser::_attr_ deserializer_tag;
  
  typedef typename remove_cvrp<VT>::type value_type;

  VT& operator()(V& v) const
  {
    return v.*m;
  }

  const VT& operator()(const V& v) const
  {
    return v.*m;
  }
};

}}

#endif
