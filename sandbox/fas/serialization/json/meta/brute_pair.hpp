//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_BRUTE_PAIR_HPP
#define FAS_SERIALIZATION_JSON_META_BRUTE_PAIR_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/primary_list.hpp>
#include <fas/serialization/json/meta/brute_list.hpp>
#include <fas/serialization/json/meta/metalist.hpp>

#include <fas/type_list/is_type_list.hpp>
#include <fas/typemanip/if_c.hpp>

namespace fas{ namespace json{

template<typename L, typename R>
struct brute_pair
{
  typedef metalist::sequence metatype;
  
  typedef typename if_c< is_type_list<L>::value, primary_list<L>, L >::type first_target;
  typedef typename if_c< is_type_list<R>::value, brute_list<R>, R >::type second_target;

  typedef ser::_brute_pair_ serializer_tag;
  typedef deser::_brute_pair_ deserializer_tag;
};

}}

#endif
