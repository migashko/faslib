#ifndef FAS_SERIALIZATION_JSON_META_BOOLEAN_HPP
#define FAS_SERIALIZATION_JSON_META_BOOLEAN_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>

namespace fas{ namespace json{

struct boolean
{
  typedef metalist::boolean metatype;
  typedef ser::_boolean_ serializer_tag;
  typedef deser::_boolean_ deserializer_tag;
};

}}

#endif
