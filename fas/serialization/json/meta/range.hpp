#ifndef FAS_SERIALIZATION_JSON_META_RANGE_HPP
#define FAS_SERIALIZATION_JSON_META_RANGE_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>


namespace fas{ namespace json{

struct range
{
  typedef metalist::any metatype;
  typedef ser::_range_ serializer_tag;
  typedef deser::_range_ deserializer_tag;
};

}}

#endif
