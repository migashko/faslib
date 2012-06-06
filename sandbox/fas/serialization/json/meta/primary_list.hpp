#ifndef FAS_SERIALIZATION_JSON_META_PRIMARY_LIST_HPP
#define FAS_SERIALIZATION_JSON_META_PRIMARY_LIST_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>

#include <fas/type_list/normalize.hpp>

namespace fas{ namespace json{

template<typename L>
struct primary_list
{
  typedef metalist::sequence metatype;
  typedef typename normalize<L>::type target_list;

  typedef ser::_primary_list_ serializer_tag;
  typedef deser::_primary_list_ deserializer_tag;
};

}}

#endif
