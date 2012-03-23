#ifndef FAS_JSONRPC_RAW_OBJECT_JSON_HPP
#define FAS_JSONRPC_RAW_OBJECT_JSON_HPP

#include <fas/jsonrpc/raw_object.hpp>
#include <fas/jsonrpc/names.hpp>

#include <fas/serialization/json/meta.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;
  
typedef aj::object<
  type_list_n<
    aj::member< n_jsonrpc, aj::attr< raw_object, raw_object::version_type, &raw_object::version, aj::string  > >,
    aj::member< n_method,  aj::attr< raw_object, raw_object::method_type,  &raw_object::method,  aj::string  > >,
    aj::member< n_params,  aj::attr< raw_object, raw_object::raw_type,     &raw_object::params,  aj::raw     > >,
    aj::member< n_id,      aj::attr< raw_object, int,                      &raw_object::id,      aj::integer > >,
    aj::member< n_result,  aj::attr< raw_object, raw_object::raw_type,     &raw_object::result,  aj::raw     > >,
    aj::member< n_error,   aj::attr< raw_object, raw_object::raw_type,     &raw_object::error,   aj::raw     > >
  >::type
> raw_object_json_type;

typedef aj::readonly< raw_object_json_type > raw_object_json;

}}

#endif
