#ifndef FAS_SERIALIZATION_JSON_META_NULL_HPP
#define FAS_SERIALIZATION_JSON_META_NULL_HPP

#include <fas/serialization/json/meta/traw.hpp>
#include <fas/typemanip/tstring.hpp>

namespace fas{ namespace json{
  
FAS_STRING(null_value, "null");

struct null: traw< null_value > {};

}}

#endif
