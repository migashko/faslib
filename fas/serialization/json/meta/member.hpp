#ifndef FAS_SERIALIZATION_JSON_META_MEMBER_HPP
#define FAS_SERIALIZATION_JSON_META_MEMBER_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/tstring.hpp>

#include <fas/typemanip/metalist.hpp>
#include <fas/typemanip/is_has_metatype.hpp>
#include <fas/typemanip/empty_type.hpp>
#include <fas/typemanip/switch_.hpp>

#include <fas/typemanip/case_.hpp>
#include <fas/typemanip/default_.hpp>
#include <fas/serialization/json/meta/is_string.hpp>
#include <fas/serialization/json/meta/metalist.hpp>

namespace fas{ namespace json{


template<typename L, typename R>
struct member
{
  typedef metalist::member metatype;

  typedef typename switch_<
    typename type_list_n<
      case_c< is_string< L >::value, L>,
      case_c< is_has_metatype< L, ::fas::metalist::tstring >::value, tstring<L> >,
      default_< L >
    >::type
  >::type target1;
  typedef R target2;
  typedef ser::_member_ serializer_tag;
  typedef deser::_member_ deserializer_tag;
};


}}

#endif
