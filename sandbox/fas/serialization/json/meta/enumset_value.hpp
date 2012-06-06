#ifndef FAS_SERIALIZATION_JSON_META_ENUMSET_VALUE_HPP
#define FAS_SERIALIZATION_JSON_META_ENUMSET_VALUE_HPP

#include <fas/serialization/json/meta/is_string.hpp>
#include <fas/serialization/json/meta/tstring.hpp>

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/metalist.hpp>

#include <fas/typemanip/metalist.hpp>
#include <fas/typemanip/switch_.hpp>
#include <fas/typemanip/case_.hpp>
#include <fas/typemanip/default_.hpp>

#include <fas/type_list/type_list_n.hpp>

#include <fas/integral/int_.hpp>

namespace fas{ namespace json{

template<typename N, int value>
struct enumset_value: int_<value>
{
  typedef metalist::string metatype;
  typedef ser::_enumset_value_ serializer_tag;
  typedef deser::_enumset_value_ deserializer_tag;

  typedef typename switch_<
    case_c< is_string< N >::value, N>,
    case_c< is_has_metatype< N, ::fas::metalist::tstring >::value, tstring<N> >,
    default_< N >
  >::type target;
};

}}

#endif
