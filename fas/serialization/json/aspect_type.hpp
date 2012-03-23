#ifndef FAS_SERIALIZATION_JSON_ASPECT_TYPE_HPP
#define FAS_SERIALIZATION_JSON_ASPECT_TYPE_HPP

#include <fas/serialization/parser/aspect.hpp>
#include <fas/serialization/ser/aspect.hpp>
#include <fas/serialization/deser/aspect.hpp>

#include <fas/aop/aspect_merge.hpp>

namespace fas{ namespace json{
  
/*

typedef ::fas::aspect_merge<
  parser::aspect,
  deser::aspect,
>::type deserializer_aspect_type;

struct deserializer_aspect
  : deserializer_aspect_type
{
};

typedef ser::aspect serializer_aspect;  

typedef ::fas::aspect_merge<
  serializer_aspect
  deserializer_aspect
>::type aspect_type;

*/

}}

#endif
