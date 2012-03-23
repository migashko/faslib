#ifndef FAS_JSONRPC_IDS_HPP
#define FAS_JSONRPC_IDS_HPP

#include <fas/aop/advice.hpp>
#include <fas/rpc/json/tags.hpp>
#include <fas/rpc/json/method/ad_ids.hpp>

namespace fas{ namespace jsonrpc{ 

struct ids: advice< _ids_, ad_ids<> > {};
struct ids_simple: advice< _ids_, ad_ids_simple > {};
struct ids_empty: advice< _ids_, ad_ids_empty > {};
  
}}

#endif
