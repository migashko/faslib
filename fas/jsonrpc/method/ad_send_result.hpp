#ifndef FAS_JSONRPC_METHOD_AD_SEND_RESULT_HPP
#define FAS_JSONRPC_METHOD_AD_SEND_RESULT_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>
//#include <fas/jsonrpc/response_object.hpp>
//#include <fas/jsonrpc/response_object_json.hpp>
//#include <fas/adv/ad_aspect_select.hpp>
//#include <fas/range/range.hpp>

namespace fas{ namespace jsonrpc{ 
  
struct ad_send_result
{
  template<typename T, typename M, typename V>
  void operator()(T& t, M& , const V& result, int id)
  {
    typedef typename M::aspect::template advice_cast<_result_value_>::type result_value;
    typedef typename M::aspect::template advice_cast<_result_json_>::type result_json;
    
    t.get_aspect().template get<_send_>()( t, result_json(), result_value(result, id) );
  }
};


}}

#endif
