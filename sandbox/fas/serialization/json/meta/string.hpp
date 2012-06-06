#ifndef FAS_SERIALIZATION_JSON_META_STRING_HPP
#define FAS_SERIALIZATION_JSON_META_STRING_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>


namespace fas{ namespace json{

struct string
{
  typedef metalist::string metatype;
  typedef ser::_string_ serializer_tag;
  typedef deser::_string_ deserializer_tag;

  enum  { limit = 0 };
};

template<int N>
struct pstring
{
  typedef metalist::string metatype;
  typedef ser::_string_ serializer_tag;
  typedef deser::_string_ deserializer_tag;

  enum  { limit = N };
};

}}

#endif
