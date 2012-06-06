#ifndef FAS_SERIALIZATION_JSON_META_POINTER_HPP
#define FAS_SERIALIZATION_JSON_META_POINTER_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/meta/metalist.hpp>

namespace fas{ namespace json{

template<typename T>
struct pointer
{
  typedef metalist::any metatype;
  typedef ser::_pointer_ serializer_tag;
  typedef deser::_pointer_ deserializer_tag;

  typedef T target;
  
};

}}

#endif
