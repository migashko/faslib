//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_JSON_META_ARRAY_HPP
#define FAS_SERIALIZATION_JSON_META_ARRAY_HPP

#include <fas/serialization/json/ser/tags.hpp>
#include <fas/serialization/json/deser/tags.hpp>

#include <fas/serialization/json/meta/primary_list.hpp>
#include <fas/serialization/json/meta/sequence.hpp>
#include <fas/serialization/json/meta/is_sequence.hpp>
#include <fas/serialization/json/meta/metalist.hpp>

#include <fas/serialization/has_serializer_tag.hpp>

#include <fas/typemanip/switch_.hpp>
#include <fas/typemanip/case_.hpp>
#include <fas/typemanip/default_.hpp>
#include <fas/typemanip/empty_type.hpp>

#include <fas/type_list/is_type_list.hpp>

namespace fas { namespace json {

template<typename J>
struct array
{
  typedef metalist::array metatype;
  
  typedef typename switch_< 
    case_< is_type_list<J>, primary_list<J> >,
    case_< is_sequence<J>, J >,
    case_< has_serializer_tag<J>, sequence<J> >,
    case_< has_deserializer_tag<J>, sequence<J> >,
    default_< empty_type >
  >::type target;

  typedef ser::_array_ serializer_tag;
  typedef deser::_array_ deserializer_tag;
};

}}

#endif
