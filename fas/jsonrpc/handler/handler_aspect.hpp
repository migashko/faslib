#ifndef FAS_JSONRPC_HANDLER_HANDLER_ASPECT_HPP
#define FAS_JSONRPC_HANDLER_HANDLER_ASPECT_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/value_advice.hpp>
#include <fas/type_list/type_list_n.hpp>

#include <fas/jsonrpc/handler/ad_output.hpp>
#include <fas/jsonrpc/aspect.hpp>

namespace fas{ namespace jsonrpc{

struct handler_list: type_list_n<
  advice< _output_, ad_output>,
  value_advice< _buffer_, std::string >,
  ::fas::jsonrpc::aspect
>::type {};

struct handler_aspect:
  ::fas::aspect< handler_list >
{};

}}

#endif
