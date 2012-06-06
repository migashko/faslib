#ifndef FAS_SERIALIZATION_JSON_META_WRITEONLY_HPP
#define FAS_SERIALIZATION_JSON_META_WRITEONLY_HPP

#include <fas/serialization/json/deser/tags.hpp>

namespace fas{ namespace json{

template<typename T>
struct writeonly: T
{
  typedef deser::_stub_ deserializer_tag;
};

}}

#endif
