#ifndef FAS_SERIALIZATION_JSON_META_SEQUENCE_HPP
#define FAS_SERIALIZATION_JSON_META_SEQUENCE_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>

namespace fas{ namespace json{

template<typename M, int N = -1>
struct sequence
{
  enum { limit = N};
  typedef metalist::sequence metatype;
  typedef M target;
  typedef ser::_sequence_ serializer_tag;
  typedef deser::_sequence_ deserializer_tag;
};

/*
 * ????
template<typename M>
struct sequence< sequence<M> >: sequence<M> {};
*/

}}

#endif
