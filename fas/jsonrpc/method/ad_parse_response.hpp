#ifndef FAS_JSONRPC_METHOD_AD_PARSE_RESPONSE_HPP
#define FAS_JSONRPC_METHOD_AD_PARSE_RESPONSE_HPP

#include <fas/jsonrpc/json/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>

namespace fas{ namespace jsonrpc{ 

template<typename V, typename J>
struct ad_parse_response : V
{
  typedef V super;
  typedef V response_value;
  typedef J response_json;
  template<typename T, typename M, typename R>
  void operator()(T& t, M& m, R r, int id)
  {
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    typename response_value::value_type value = super::operator()(t);
    
    deserializer ds;
    ds( response_json(), value, r );

    //!! Удалить id из ids
    
    if ( !ds )
      ;
      //?? t.get_aspect().template get<_invalid_response_>()(t, id);
      //!!  t.get_aspect().template get<_invalid_request_>()(t, id);
    else
      m.get_aspect().template get<_response_handler_>()(t, m, value, id);
    
  }
};


}}

#endif
