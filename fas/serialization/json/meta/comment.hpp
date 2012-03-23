#ifndef FAS_SERIALIZATION_JSON_META_COMMENT_HPP
#define FAS_SERIALIZATION_JSON_META_COMMENT_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

//#include <fas/range/range.hpp>
#include <fas/range/string_range.hpp>

#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/typemanip/empty_type.hpp>

namespace fas{ namespace json{

template<typename C1, typename M, typename C2 = empty_type >
struct comment;

  
template<typename C1, typename M, typename C2 >
struct comment: M
{
  typedef ser::_comment_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
  typedef M target;
  
  typedef C1 before_comment;
  typedef C2 after_comment;
  
  typedef string_range< typename before_comment::value_type > before_range_type;
  typedef string_range< typename after_comment::value_type > after_range_type;
  
  before_range_type before_range() const
  {
    return before_range_type ( before_comment()() );
  }

  after_range_type after_range() const
  {
    return after_range_type( after_comment()() );
  }
};

template<typename C1, typename M>
struct comment<C1, M, empty_type>
  : M
{
  typedef ser::_comment_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
  typedef M target;
  
  typedef C1 before_comment;
  typedef empty_type after_comment;
  
  typedef string_range< typename before_comment::value_type > before_range_type;

  before_range_type before_range() const
  {
    return before_range_type( before_comment()() );
  }
};

template<typename M, typename C2 >
struct comment<empty_type, M, C2>
  : M
{
  typedef ser::_comment_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
  typedef M target;
  
  typedef empty_type before_comment;
  typedef C2 after_comment;

  typedef string_range< typename after_comment::value_type > after_range_type;
  after_range_type after_range() const
  {
    return after_range_type( after_comment()() );
  }
};

template<typename M>
struct comment<empty_type, M, empty_type>
  : M
{
  typedef ser::_comment_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
  
  typedef M target;
  
  typedef empty_type before_comment;
  typedef empty_type after_comment;
};

}}

#endif
