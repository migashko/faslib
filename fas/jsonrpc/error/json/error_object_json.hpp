#ifndef FAS_JSONRPC_ERROR_JSON_ERROR_OBJECT_JSON_HPP
#define FAS_JSONRPC_ERROR_JSON_ERROR_OBJECT_JSON_HPP

#include <fas/jsonrpc/names.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;
  
template< typename O, typename V, typename J >
struct custom_error_message_json:
  aj::object<
    typename type_list_n<
      aj::member< n_jsonrpc, aj::tstring<version> >,
      aj::member< n_error,   aj::attr< O, const V* ,  &O::error,  aj::pointer<J> > >,
      aj::member< n_id,      aj::attr< O, int, &O::id,      aj::integer > >
    >::type
  >
{
};

template< typename O, typename J >
struct custom_error_notify_json:
  aj::object<
    typename type_list_n<
      aj::member< n_jsonrpc, aj::tstring<version> >,
      aj::member< n_error,   J >
    >::type
  >
{
};

}}

#endif
