#ifndef FAS_SERIALIZATION_JSON_META_TRAW_HPP
#define FAS_SERIALIZATION_JSON_META_TRAW_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/meta/metalist.hpp>

#include <fas/range/string_range.hpp>

namespace fas{ namespace json{

template<typename N>
struct traw
{
  typedef metalist::any metatype;

  typedef ser::_traw_ serializer_tag;
  typedef deser::_traw_ deserializer_tag;
  typedef string_range< typename N::value_type > range_type;
  
  typename N::value_type operator()() const 
  {
    return  N()();
  }

  range_type get_range() const
  {
    return range_type( N()() );
  }
};

}}

#endif
