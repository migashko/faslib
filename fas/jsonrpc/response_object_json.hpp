#ifndef FAS_JSONRPC_RESPONSE_OBJECT_JSON_HPP
#define FAS_JSONRPC_RESPONSE_OBJECT_JSON_HPP

#include <fas/jsonrpc/names.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;
  
template<typename ResultJson, typename Obj >
struct response_object_json:
  aj::object<
    typename type_list_n<
      aj::member< n_jsonrpc, aj::tstring<version> >,
      aj::member< n_result,  aj::attr< Obj, typename Obj::result_type , &Obj::result,  aj::pointer<ResultJson> > >,
      aj::member< n_id,      aj::attr< Obj, int,                        &Obj::id,      aj::integer > >
    >::type
  >
{
};

}}

#endif
