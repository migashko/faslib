#ifndef FAS_JSONRPC_OUTGOING_JSON_ERROR_NOTIFY_JSON_HPP
#define FAS_JSONRPC_OUTGOING_JSON_ERROR_NOTIFY_JSON_HPP

#include <fas/jsonrpc/names.hpp>

#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/member.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/serialization/json/meta/null.hpp>

#include <string>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;
  
template< typename O, typename J >
struct error_notify_json:
  aj::object<
    typename type_list_n<
      aj::member< n_jsonrpc, aj::tstring<version> >,
      aj::member< n_error,   J >,
      aj::member< n_id, aj::null >
    >::type
  >
{
};

}}

#endif

