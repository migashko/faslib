#ifndef FAS_RPC_JSON_METHOD_NOTIFY_JSON_HPP
#define FAS_RPC_JSON_METHOD_NOTIFY_JSON_HPP

#include <fas/aop/definition.hpp>
#include <fas/aop/advice.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/rpc/json/tags.hpp>
#include <fas/rpc/json/method/ad_invoke_notify_handler.hpp>

namespace fas{ namespace rpc{ namespace json{

template<typename J  >
struct notify_json
  : type_list_n<
      definition<_notify_json_, J >,
      advice< _invoke_notify_handler_, ad_invoke_notify_handler>
    >::type
{
};


}}}

#endif
