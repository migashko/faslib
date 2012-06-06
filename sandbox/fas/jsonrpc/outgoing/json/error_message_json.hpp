#ifndef FAS_JSONRPC_OUTGOING_JSON_ERROR_MESSAGE_JSON_HPP
#define FAS_JSONRPC_OUTGOING_JSON_ERROR_MESSAGE_JSON_HPP

#include <fas/jsonrpc/names.hpp>

#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/field.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/serialization/json/meta/pointer.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/tstring.hpp>

#include <string>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;
  
template< typename O, typename V, typename J >
struct error_message_json:
  aj::object<
    typename type_list_n<
      aj::field< n_jsonrpc, aj::tstring<version> >,
      aj::field< n_error,   aj::attr< O, const V* ,  &O::error,  aj::pointer<J> > >,
      aj::field< n_id,      aj::attr< O, int, &O::id,      aj::integer > >
    >::type
  >
{
};

}}

#endif
