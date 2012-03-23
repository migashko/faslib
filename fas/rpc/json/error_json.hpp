#ifndef FAS_RPC_JSON_ERROR_JSON_HPP
#define FAS_RPC_JSON_ERROR_JSON_HPP

#include <fas/rpc/json/error.hpp>
#include <fas/rpc/json/names.hpp>
#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/member.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace rpc{ namespace json{

typedef aj::object<
  type_list_n<
    aj::member<n_code, aj::attr< error, int, &error::code, aj::integer> >,
    aj::member<n_message, aj::attr< error, std::string, &error::message, aj::integer> >
  >::type
> error_json;


}}}

#endif
