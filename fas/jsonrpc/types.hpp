#ifndef FAS_JSONRPC_TYPES_HPP
#define FAS_JSONRPC_TYPES_HPP

#include <fas/serialization/json/meta/integer.hpp>

namespace fas{ namespace jsonrpc{

#ifndef FAS_JSONRPC_ID_TYPE
typedef int id_t;
#else
typedef FAS_JSONRPC_ID_TYPE id_t;
#endif

#ifndef FAS_JSONRPC_ID_JSON
typedef fas::json::integer id_json;
#else
typedef FAS_JSONRPC_ID_JSON id_json;
#endif



 
}}

#endif
