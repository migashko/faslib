#ifndef FAS_SERIALIZATION_JSON_META_BLOCK_HPP
#define FAS_SERIALIZATION_JSON_META_BLOCK_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

namespace fas{ namespace json{

template<typename M>
struct block
  : M
{
  typedef ser::_block_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
  typedef M target;
};

}}

#endif
