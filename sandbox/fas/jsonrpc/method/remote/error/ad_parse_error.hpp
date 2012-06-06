#ifndef FAS_JSONRPC_METHOD_REMOTE_ERROR_AD_PARSE_ERROR_HPP
#define FAS_JSONRPC_METHOD_REMOTE_ERROR_AD_PARSE_ERROR_HPP

#include <fas/jsonrpc/inbound/tags.hpp>
#include <fas/jsonrpc/method/remote/error/tags.hpp>
#include <fas/jsonrpc/method/remote/request/tags.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

template<typename V, typename J>
struct ad_parse_error : V
{
  typedef V super;
  typedef V error_holder;
  typedef J error_json;
  
  template<typename T, typename M, typename R>
  void operator()(T& t, M& method, R r, int id)
  {
    typedef typename T::aspect::template advice_cast<_deserializer_>::type deserializer;
    typedef ::fas::jsonrpc::_id_ _global_id_;
    
    typename error_holder::value_type error = super::operator()(t);
    
    
    register bool valid_id = method.get_aspect().template get<_id_>().has(id);
    
    if ( valid_id )
    {
      method.get_aspect().template get<_id_>().pop(id);
      t.get_aspect().template get<_global_id_>().pop(id);
    }
    
    deserializer ds;

    std::cout << "[" << std::string( r.begin(), r.end() ) << "]" << std::endl;
    ds( error_json(), error, r );
    
    if ( !ds )
      method.get_aspect().template get<_invalid_error_>()(t, method, r,  id);
    else if ( !valid_id)
      method.get_aspect().template get<_invalid_error_id_>()(t, method, error, id);
    else 
      method.get_aspect().template get<_error_handler_>()(t, method, error, id); 
  }
};


}}}

#endif
