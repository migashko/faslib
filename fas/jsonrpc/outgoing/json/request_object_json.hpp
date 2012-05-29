#ifndef FAS_JSONRPC_OUTGOING_TYPES_REQUEST_OBJECT_JSON_HPP
#define FAS_JSONRPC_OUTGOING_TYPES_REQUEST_OBJECT_JSON_HPP

#include <fas/jsonrpc/names.hpp>
#include <fas/jsonrpc/types.hpp>
#include <fas/serialization/json/meta.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;
  
template< typename Name, typename O, typename V, typename J >
struct request_object_json:
  aj::object<
    typename type_list_n<
      aj::field< n_jsonrpc, aj::tstring<version> >,
      aj::field< n_method,  aj::tstring<Name> >,
      aj::field< n_params,  aj::attr< O, const V* ,  &O::params,  aj::pointer<J> > >,
      aj::field< n_id,      aj::attr< O, id_t, &O::id,  id_json > >
    >::type
  >
{
};

}}

#endif
