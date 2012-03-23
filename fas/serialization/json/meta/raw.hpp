#ifndef FAS_SERIALIZATION_JSON_META_RAW_HPP
#define FAS_SERIALIZATION_JSON_META_RAW_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/meta/metalist.hpp>

namespace fas{ namespace json{

struct raw
{
  typedef metalist::any metatype;
  typedef ser::_raw_ serializer_tag;
  typedef deser::_raw_ deserializer_tag;
};

}}

#endif
