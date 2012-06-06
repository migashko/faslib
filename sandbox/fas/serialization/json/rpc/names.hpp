#ifndef FAS_SERIALIZATION_JSON_RPC_NAMES_HPP
#define FAS_SERIALIZATION_JSON_RPC_NAMES_HPP

#include <fas/typemanip/tstring.hpp>

namespace fas{ namespace json{ namespace rpc{

FAS_NAME(jsonrpc)
FAS_STRING(version, "2.0")
FAS_NAME(id)
FAS_NAME(method)
FAS_NAME(params)
FAS_NAME(result)
FAS_NAME(error)

}}}

#endif