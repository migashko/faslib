#ifndef FAS_SERIALIZATION_JSON_META_SETTER_HPP
#define FAS_SERIALIZATION_JSON_META_SETTER_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>
#include <fas/typemanip/remove_cvrp.hpp>

namespace fas{ namespace json{

template<typename V, typename VT, void (V::* m)(VT), typename M>
struct setterx
{
  typedef typename M::metatype metatype;
  typedef M target;
  
  typedef ser::_stub_ serializer_tag;
  typedef deser::_prop_ deserializer_tag;
  
  typedef typename remove_cvrp<VT>::type value_type;
  
  void set(V& v, VT value) const
  {
    (v.*m)(value);
  }
};

}}

#endif
