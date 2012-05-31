#ifndef FAS_SERIALIZATION_JSON_PARSER_ASPECT_TYPE_HPP
#define FAS_SERIALIZATION_JSON_PARSER_ASPECT_TYPE_HPP


#include <fas/serialization/json/parser/ad_null.hpp>
#include <fas/serialization/json/parser/ad_boolean.hpp>
#include <fas/serialization/json/parser/ad_number.hpp>
#include <fas/serialization/json/parser/ad_string.hpp>
#include <fas/serialization/json/parser/ad_value.hpp>
#include <fas/serialization/json/parser/ad_item.hpp>
#include <fas/serialization/json/parser/ad_array.hpp>

#include <fas/serialization/json/parser/ad_field.hpp>
#include <fas/serialization/json/parser/ad_object.hpp>
#include <fas/serialization/json/parser/ad_space.hpp>
#include <fas/serialization/json/except/ad_except.hpp>

#include <fas/serialization/json/parser/tags.hpp>
#include <fas/serialization/json/except/tags.hpp>

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>

#include <fas/type_list/type_list_n.hpp>


namespace fas{ namespace json{ namespace parse{

typedef
  ::fas::aspect<
    type_list_n<
      aspect_space,
      advice<_null_, ad_null>,
      advice<_boolean_, ad_boolean>,
      advice<_number_, ad_number>,
      advice<_string_, ad_string>,
      advice<_value_, ad_value>,
      //advice<_sequence_, ad_sequence>,
      advice<_array_, ad_array>,
      advice<_item_, ad_item>,
      advice<_object_, ad_object>,
      // advice<_space_, ad_space>,
      advice<_name_, ad_string>,
      advice<_field_, ad_field>,
      advice<_except_, ad_except>
    >::type
  > aspect_type;

}}}

#endif
