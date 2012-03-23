#ifndef FAS_SERIALIZATION_JSON_META_REFSET_HPP
#define FAS_SERIALIZATION_JSON_META_REFSET_HPP

/*
#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/serialization/json/meta/metalist.hpp>
*/

namespace fas{ namespace json{

/*
template<typename V, typename VT, VT (V::* m)(void), typename M>
struct refset
{
  typedef typename M::metatype metatype;
  typedef M target;
  
  typedef ser::_stub_ serializer_tag;
  typedef deser::_attr_ deserializer_tag;
  
  typedef VT value_type;

  value_type ref_value(V& v) const
  {
    return (v.*m)();
  }
};
*/

}}

#endif
