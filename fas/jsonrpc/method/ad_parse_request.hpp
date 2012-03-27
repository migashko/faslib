#ifndef FAS_JSONRPC_METHOD_AD_PARSE_REQUEST_HPP
#define FAS_JSONRPC_METHOD_AD_PARSE_REQUEST_HPP

#include <fas/jsonrpc/json/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>
#include <fas/adv/ad_aspect_select.hpp>

namespace fas{ namespace jsonrpc{ 

template<typename V, typename J>
struct ad_parse_request : V
{
  typedef V super;
  typedef V request_value;
  typedef J request_json;
  template<typename T, typename M, typename R>
  void operator()(T& t, M& method, R r, int id)
  {
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    typename request_value::value_type value = super::operator()(t);

    register bool valid_id = id > 0 && !method.get_aspect().template get<_method_id_>().has(id);
    

    if ( valid_id )
      method.get_aspect().template get<_method_id_>().push(id);
    
    deserializer ds;
    ds( request_json(), value, r );
    
    if ( !ds )
    {
      if ( valid_id )
        method.get_aspect().template get<_method_id_>().pop(id);
      
      method.get_aspect().template get<_invalid_request_>()(t, method, r, id);
    }
    else if ( !valid_id)
      method.get_aspect().template get<_invalid_id_>()(t, method, value, id);
    else 
      method.get_aspect().template get<_request_handler_>()(t, method, value, id); 
  }
};


}}

#endif
