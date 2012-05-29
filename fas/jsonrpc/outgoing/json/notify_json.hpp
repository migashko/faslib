#ifndef FAS_JSONRPC_OUTGOING_JSON_NOTIFY_JSON_HPP
#define FAS_JSONRPC_OUTGOING_JSON_NOTIFY_JSON_HPP

#include <fas/jsonrpc/names.hpp>

#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/field.hpp>
#include <fas/serialization/json/meta/tstring.hpp>
#include <fas/serialization/json/meta/null.hpp>

#include <fas/type_list/type_list_n.hpp>

#include <string>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;
  
template< typename Name, typename J >
struct notify_json:
  aj::object<
    typename type_list_n<
      aj::field< n_jsonrpc, aj::tstring<version> >,
      aj::field< n_method, aj::tstring<Name> >,
      aj::field< n_params,   J >
    >::type
  >
{
};

}}

#endif

