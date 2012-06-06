#ifndef FAS_SERIALIZATION_JSON_META_READONLY_HPP
#define FAS_SERIALIZATION_JSON_META_READONLY_HPP

#include <fas/serialization/json/ser/tags.hpp>

namespace fas{ namespace json{

template<typename T>
struct readonly: T
{
  /*typedef typename T::metatype metatype;
  typedef typename T::deserializer_tag deserializer_tag;
  */
  typedef ser::_stub_ serializer_tag;
};

}}

#endif
