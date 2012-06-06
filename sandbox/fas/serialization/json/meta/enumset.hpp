#ifndef FAS_SERIALIZATION_JSON_META_ENUMSET_HPP
#define FAS_SERIALIZATION_JSON_META_ENUMSET_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>
#include <fas/serialization/json/meta/primary_list.hpp>

#include <fas/type_list/is_type_list.hpp>
#include <fas/typemanip/if_c.hpp>

namespace fas{ namespace json{

template<typename L>
struct enumset
{
  typedef metalist::array metatype;;
  typedef typename if_c< is_type_list<L>::value, primary_list<L>, L >::type target;
  
  typedef ser::_enumset_ serializer_tag;
  typedef deser::_enumset_ deserializer_tag;
};


}}

#endif
