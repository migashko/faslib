#ifndef FAS_SERIALIZATION_JSON_META_REAL_HPP
#define FAS_SERIALIZATION_JSON_META_REAL_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>

namespace fas{ namespace json{

struct real
{
  typedef metalist::number metatype;
  typedef ser::_real_ serializer_tag;
  typedef deser::_real_ deserializer_tag;
};

}}

#endif
