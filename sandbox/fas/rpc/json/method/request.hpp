#ifndef FAS_RPC_JSON_METHOD_REQUEST_HPP
#define FAS_RPC_JSON_METHOD_REQUEST_HPP

#include <fas/rpc/json/method/ad_ids.hpp>
#include <fas/rpc/json/tags.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>

namespace fas{ namespace rpc{ namespace json{

template<typename H>
struct request
  : aspect< 
      typename type_list_n<
        advice<_request_, H >,
        advice<_ids_, ad_ids<> > 
      >::type
    >
{
  
};
  
}}}

#endif
