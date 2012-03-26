#ifndef FAS_JSONRPC_METHOD_AD_PARSE_REQUEST_HPP
#define FAS_JSONRPC_METHOD_AD_PARSE_REQUEST_HPP

#include <fas/jsonrpc/json/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>
#include <fas/adv/ad_aspect_select.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_parse_request
{
  template<typename T, typename M, typename R>
  void operator()(T& t, M& m, R r, int id)
  {
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    typedef typename M::aspect::template advice_cast<_request_value_>::type request_value;
    typedef typename M::aspect::template advice_cast<_request_json_>::type request_json;
    
    typename request_value::value_type value = m.get_aspect().template get<_request_value_>()(t);
    
    deserializer ds;
    ds( request_json(), value, r );
    
    if ( !ds )
      t.get_aspect().template get<_invalid_request_>()(t, id);
    else
      m.get_aspect().template get<_request_handler_>()(t, m, value, id); 
    
  }
};


}}

#endif
