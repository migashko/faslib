#ifndef FAS_RPC_JSON_METHOD_IDS_HPP
#define FAS_RPC_JSON_METHOD_IDS_HPP

#include <fas/aop/advice.hpp>
#include <fas/rpc/json/tags.hpp>
#include <fas/rpc/json/method/ad_ids.hpp>

namespace fas{ namespace rpc{ namespace json{

struct ids: advice< _ids_, ad_ids<> > {};
struct ids_simple: advice< _ids_, ad_ids_simple > {};
struct ids_empty: advice< _ids_, ad_ids_empty > {};
  
}}}

#endif
