#ifndef FAS_SERIALIZATION_JSON_RPC_ERROR_HPP
#define FAS_SERIALIZATION_JSON_RPC_ERROR_HPP

namespace fas{ namespace json{ namespace rpc{
  
struct error
{
  int code;
  std::string message;
};
  
}}}

#endif
