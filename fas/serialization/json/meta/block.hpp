//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_BLOCK_HPP
#define FAS_SERIALIZATION_JSON_META_BLOCK_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

namespace fas{ namespace json{

template<typename J>
struct block
  : J
{
  typedef ser::_block_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
  typedef J target;

};

}}

#endif
