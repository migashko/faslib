#ifndef FAS_SERIALIZATION_JSON_META_STUB_HPP
#define FAS_SERIALIZATION_JSON_META_STUB_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

namespace fas{ namespace json{

struct stub
{
  typedef ser::_stub_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
};

}}

#endif
