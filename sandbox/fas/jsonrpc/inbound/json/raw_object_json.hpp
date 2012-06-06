#ifndef FAS_JSONRPC_INBOUND_JSON_RAW_OBJECT_JSON_HPP
#define FAS_JSONRPC_INBOUND_JSON_RAW_OBJECT_JSON_HPP

#include <fas/jsonrpc/inbound/types/raw_object.hpp>
#include <fas/jsonrpc/names.hpp>

#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/raw.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/field.hpp>
#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/readonly.hpp>


#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;
  
typedef aj::object<
  type_list_n<
    aj::field< n_jsonrpc, aj::attr< raw_object, raw_object::version_type, &raw_object::version, aj::string  > >,
    aj::field< n_method,  aj::attr< raw_object, raw_object::method_type,  &raw_object::method,  aj::string  > >,
    aj::field< n_params,  aj::attr< raw_object, raw_object::raw_type,     &raw_object::params,  aj::raw     > >,
    aj::field< n_id,      aj::attr< raw_object, int,                      &raw_object::id,      aj::integer > >,
    aj::field< n_result,  aj::attr< raw_object, raw_object::raw_type,     &raw_object::result,  aj::raw     > >,
    aj::field< n_error,   aj::attr< raw_object, raw_object::raw_type,     &raw_object::error,   aj::raw     > >
  >::type
> raw_object_json_type;

typedef aj::readonly< raw_object_json_type > raw_object_json;

}}

#endif
