//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_COMMENT_HPP
#define FAS_SERIALIZATION_JSON_META_COMMENT_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/range/string_range.hpp>

#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/typemanip/empty_type.hpp>

namespace fas{ namespace json{

template<typename C1, typename J, typename C2 = empty_type >
struct comment;

  
template<typename C1, typename J, typename C2 >
struct comment: J
{
  typedef ser::_comment_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
  typedef J target;
  
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

template<typename C1, typename J>
struct comment<C1, J, empty_type>
  : J
{
  typedef ser::_comment_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
  
  typedef J target;
  typedef C1 before_comment;
  typedef empty_type after_comment;
  
  typedef string_range< typename before_comment::value_type > before_range_type;

  before_range_type before_range() const
  {
    return before_range_type( before_comment()() );
  }
};

template<typename J, typename C2 >
struct comment<empty_type, J, C2>
  : J
{
  typedef ser::_comment_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
  typedef J target;
  
  typedef empty_type before_comment;
  typedef C2 after_comment;

  typedef string_range< typename after_comment::value_type > after_range_type;
  after_range_type after_range() const
  {
    return after_range_type( after_comment()() );
  }
};

template<typename J>
struct comment<empty_type, J, empty_type>
  : J
{
  typedef ser::_comment_ serializer_tag;
  typedef deser::_stub_ deserializer_tag;
  
  typedef J target;
  
  typedef empty_type before_comment;
  typedef empty_type after_comment;
};

}}

#endif
