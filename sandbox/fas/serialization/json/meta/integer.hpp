#ifndef FAS_SERIALIZATION_JSON_META_INTEGER_HPP
#define FAS_SERIALIZATION_JSON_META_INTEGER_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>

namespace fas{ namespace json{

struct integer
{
  typedef metalist::number metatype;
  typedef ser::_integer_ serializer_tag;
  typedef deser::_integer_ deserializer_tag;
};

}}

#endif
