#ifndef FAS_SERIALIZATION_JSON_META_TSTRING_HPP
#define FAS_SERIALIZATION_JSON_META_TSTRING_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>
#include <fas/range/string_range.hpp>

namespace fas{ namespace json{

template<typename N>
struct tstring
{
  typedef metalist::string metatype;

  typedef ser::_cstring_ serializer_tag;
  typedef deser::_cstring_ deserializer_tag;
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

template<const char* S>
struct cstring
{
  typedef metalist::string metatype;
  typedef ser::_cstring_ serializer_tag;
  typedef deser::_cstring_ deserializer_tag;
  typedef string_range< const char* > range_type;

  range_type get_range() const
  {
    return range_type( S );
  }
  
};

template<const wchar_t* S>
struct cwstring
{
  typedef metalist::string metatype;
  typedef ser::_cstring_ serializer_tag;
  typedef deser::_cstring_ deserializer_tag;
  typedef string_range< const wchar_t* > range_type;

  range_type get_range() const
  {
    return range_type( S );
  }
};

}}

#endif
