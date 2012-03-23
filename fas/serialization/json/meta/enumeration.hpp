#ifndef FAS_SERIALIZATION_JSON_META_ENUMERATION_HPP
#define FAS_SERIALIZATION_JSON_META_ENUMERATION_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>
#include <fas/type_list/normalize.hpp>

namespace fas{ namespace json{

template<typename L>
struct enumeration
{
  typedef metalist::string metatype;
  typedef typename normalize<L>::type target_list;
  
  typedef ser::_enum_ serializer_tag;
  typedef deser::_enum_ deserializer_tag;
};

}}

#endif
