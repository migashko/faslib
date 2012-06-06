//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_BRUTE_LIST_HPP
#define FAS_SERIALIZATION_JSON_META_BRUTE_LIST_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>
#include <fas/serialization/json/meta/metalist.hpp>
#include <fas/type_list/normalize.hpp>

namespace fas{ namespace json{

template<typename L>
struct brute_list
{
  typedef metalist::sequence metatype;
  typedef typename normalize<L>::type target_list;

  typedef ser::_brute_list_ serializer_tag;
  typedef deser::_brute_list_ deserializer_tag;
};


}}

#endif
