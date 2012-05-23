#ifndef FAS_SERIALIZATION_JSON_DESER_ASPECT_TYPE_HPP
#define FAS_SERIALIZATION_JSON_DESER_ASPECT_TYPE_HPP

//#include <fas/serialization/json/ad_except.hpp>
#include <fas/serialization/json/deser/ad_boolean.hpp>
#include <fas/serialization/json/deser/ad_integer.hpp>
#include <fas/serialization/json/deser/ad_real.hpp>
#include <fas/serialization/json/deser/ad_stub.hpp>
#include <fas/serialization/json/deser/ad_string.hpp>
#include <fas/serialization/json/deser/ad_array.hpp>
#include <fas/serialization/json/deser/ad_sequence.hpp>
#include <fas/serialization/json/deser/ad_string.hpp>
#include <fas/serialization/json/deser/ad_member.hpp>
#include <fas/serialization/json/deser/ad_enumeration.hpp>

#include <fas/serialization/json/deser/ad_object.hpp>
#include <fas/serialization/json/deser/ad_stub.hpp>
#include <fas/serialization/json/deser/ad_attr.hpp>

#include <fas/serialization/json/deser/ad_primary_list.hpp>
#include <fas/serialization/json/deser/ad_separator.hpp>
#include <fas/serialization/json/deser/ad_brute_list.hpp>
#include <fas/serialization/json/deser/ad_brute_pair.hpp>

#include <fas/serialization/json/deser/ad_range.hpp>
#include <fas/serialization/json/deser/ad_raw.hpp>
//#include <fas/serialization/json/deser/ad_traw.hpp>

#include <fas/serialization/json/deser/tags.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>

#include <fas/serialization/json/deser/tags.hpp>

namespace fas{ namespace json{ namespace deser{

typedef
  aspect<
    type_list_n<
      //advice< deser::_except_, deser::ad_except>,
      advice< deser::_stub_, deser::ad_stub>,
      advice< deser::_boolean_, deser::ad_boolean>,
      advice< deser::_integer_, deser::ad_integer>,
      advice< deser::_real_, deser::ad_real>,
      advice< deser::_string_, deser::ad_string>,
      advice< deser::_cstring_, deser::ad_cstring>,
      advice< deser::_member_, deser::ad_member>,
      advice< deser::_attr_, deser::ad_attr>,
      advice< deser::_prop_, deser::ad_prop>,
      // advice< deser::_member_list_, deser::ad_member_list>,
      //advice< deser::_field_list_, deser::ad_field_list>,
      //advice< deser::_field_list2_, deser::ad_field_list2>,
      advice< deser::_brute_pair_, deser::ad_brute_pair>,
      advice< deser::_brute_list_, deser::ad_brute_list>,
      advice< deser::_primary_list_, deser::ad_primary_list>,
			advice< deser::_separator_, deser::ad_separator>,
      advice< deser::_array_, deser::ad_array>,
      advice< deser::_sequence_, deser::ad_sequence>,
      advice< deser::_object_, deser::ad_object>,
      advice< deser::_enum_, deser::ad_enumeration>,
      advice< deser::_enum_value_, deser::ad_enum_value>,
      advice< deser::_stub_, deser::ad_stub>,
       alias< deser::_pointer_, deser::_stub_>, 
      advice< deser::_raw_, deser::ad_raw>,
      advice< deser::_traw_, deser::ad_traw>,
      advice< deser::_range_, deser::ad_range>
    >::type
  >
aspect_type;


}}}

#endif
