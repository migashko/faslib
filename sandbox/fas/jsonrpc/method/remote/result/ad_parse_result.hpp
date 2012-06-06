#ifndef FAS_JSONRPC_METHOD_REMOTE_RESULT_AD_PARSE_RESULT_HPP
#define FAS_JSONRPC_METHOD_REMOTE_RESULT_AD_PARSE_RESULT_HPP

#include <fas/jsonrpc/inbound/tags.hpp>
#include <fas/jsonrpc/method/remote/result/tags.hpp>
#include <fas/jsonrpc/method/remote/request/tags.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

template<typename V, typename J>
struct ad_parse_result : V
{
  typedef V super;
  typedef V result_holder;
  typedef J result_json;
  
  template<typename T, typename M, typename R>
  void operator()(T& t, M& method, R r, int id)
  {
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    typedef ::fas::jsonrpc::_id_ _global_id_;
    
    typename result_holder::value_type result = super::operator()(t);
    
    
    register bool valid_id = method.get_aspect().template get<_id_>().has(id);
    
    if ( valid_id )
    {
      method.get_aspect().template get<_id_>().pop(id);
      t.get_aspect().template get<_global_id_>().pop(id);
    }
    
    deserializer ds;
    ds( result_json(), result, r );
    
    if ( !ds )
      method.get_aspect().template get<_invalid_result_>()(t, method, r,  id);
    else if ( !valid_id)
      method.get_aspect().template get<_invalid_result_id_>()(t, method, result, id);
    else 
      method.get_aspect().template get<_result_handler_>()(t, method, result, id); 
  }
};


}}}

#endif
