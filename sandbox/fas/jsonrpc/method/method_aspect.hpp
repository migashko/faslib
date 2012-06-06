#ifndef FAS_JSONRPC_METHOD_ASPECT_HPP
#define FAS_JSONRPC_METHOD_ASPECT_HPP

#include <fas/aop/aspect.hpp>
#include <fas/aop/stub.hpp>
#include <fas/aop/advice.hpp>

#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace jsonrpc{

typedef type_list_n<
  stub<_context_>
>::type method_advice_list;

struct method_aspect:
  ::fas::aspect<method_advice_list>
{
};

}}

#endif

