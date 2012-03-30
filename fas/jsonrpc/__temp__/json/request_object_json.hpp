#ifndef FAS_JSONRPC_JSON_REQUEST_OBJECT_JSON_HPP
#define FAS_JSONRPC_JSON_REQUEST_OBJECT_JSON_HPP

#include <fas/jsonrpc/names.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{

namespace aj = ::fas::json;


template< typename N, typename O, typename V, typename J >
struct request_object_json:
  aj::object<
    typename type_list_n<
      aj::member< n_jsonrpc, aj::tstring<version> >,
      aj::member< n_method,  aj::tstring<N> >,
      aj::member< n_params,  aj::attr< O, const V*, &O::params,  aj::pointer<J> > >,
      aj::member< n_id,      aj::attr< O, int, &O::id, aj::integer > >
    >::type
  >
{
};

/*
template< typename NJ, typename VJ >
struct notify_object_json:
  aj::object<
    typename type_list_n<
      aj::member< n_jsonrpc, aj::tstring<version> >,
      aj::member< n_method,  aj::tstring<NJ>      >,
      aj::member< n_params,  VJ       >
    >::type
  >
{
};
*/

}}

#endif
