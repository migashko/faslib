#ifndef FAS_SERIALIZATION_JSON_SERIALIZER_ASPECT_TYPE_HPP
#define FAS_SERIALIZATION_JSON_SERIALIZER_ASPECT_TYPE_HPP

//#include <fas/serialization/json/ad_except.hpp>


#include <fas/serialization/json/ser/ad_integer.hpp>
#include <fas/serialization/json/ser/ad_real.hpp>
#include <fas/serialization/json/ser/ad_boolean.hpp>
#include <fas/serialization/json/ser/ad_array.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>
#include <fas/serialization/json/ser/ad_sequence.hpp>
#include <fas/serialization/json/ser/ad_attr.hpp>
#include <fas/serialization/json/ser/ad_enumeration.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>
#include <fas/serialization/json/ser/ad_field.hpp>
#include <fas/serialization/json/ser/ad_object.hpp>
#include <fas/serialization/json/ser/ad_stub.hpp>
#include <fas/serialization/json/ser/ad_raw.hpp>
//#include <fas/serialization/json/ser/ad_traw.hpp>
#include <fas/serialization/json/ser/ad_range.hpp>
#include <fas/serialization/json/ser/ad_enumeration.hpp>
#include <fas/serialization/json/ser/ad_enum_value.hpp>
#include <fas/serialization/json/ser/ad_primary_list.hpp>
#include <fas/serialization/json/ser/ad_brute_list.hpp>
#include <fas/serialization/json/ser/ad_brute_pair.hpp>
#include <fas/serialization/json/ser/ad_pointer.hpp>
#include <fas/serialization/json/ser/ad_null.hpp>

#include <fas/serialization/json/except/ad_except.hpp>

#include <fas/serialization/json/ser/tags.hpp>

#include <fas/serialization/json/ser/ad_block.hpp>
#include <fas/serialization/json/ser/ad_comment.hpp>

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace json{ namespace ser{

  
typedef
  aspect<
    type_list_n<
      advice< ser::_string_, ser::ad_string>,
      advice< ser::_cstring_, ser::ad_cstring>,
      advice< ser::_integer_, ser::ad_integer>,
      advice< ser::_real_, ser::ad_real>,
      advice< ser::_boolean_, ser::ad_boolean>,
      advice< ser::_enum_, ser::ad_enumeration>,
      advice< ser::_enum_value_, ser::ad_enum_value>,
      advice< ser::_attr_, ser::ad_attr>,
      advice< ser::_prop_, ser::ad_prop>,
      advice< ser::_field_, ser::ad_field>,
      //advice< ser::_field_list_, ser::ad_field_list>,
      //advice< ser::_field_list_, ser::ad_field_list>,
      advice< ser::_primary_list_, ser::ad_primary_list>,
      advice< ser::_brute_list_, ser::ad_brute_list>,
      advice< ser::_array_, ser::ad_array>,
      advice< ser::_sequence_, ser::ad_sequence>,
      advice< ser::_object_, ser::ad_object>,
      advice< ser::_stub_, ser::ad_stub>,
      advice< ser::_brute_pair_, ser::ad_brute_pair>,
      advice< ser::_block_, ser::ad_block<> >,
      advice< ser::_comment_, ser::ad_comment >,
      advice< ser::_raw_, ser::ad_raw >,
      advice< ser::_traw_, ser::ad_traw >,
      advice< ser::_range_, ser::ad_range>,
      advice< ser::_pointer_, ser::ad_pointer>,
      advice< ser::_null_, ser::ad_null>,
      advice<_except_, ad_except>
    >::type
  >
aspect_type;


}}}

#endif
