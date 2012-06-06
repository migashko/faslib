#ifndef FAS_RPC_JSON_METHOD_AD_INVOKE_REQUEST_HANDLER_HPP
#define FAS_RPC_JSON_METHOD_AD_INVOKE_REQUEST_HANDLER_HPP

#include <fas/serialization/json/rpc/method/tags.hpp>
//#include <fas/adv/ad_aspect_select.hpp>

#include <fas/serialization/json/except.hpp>

namespace fas{ namespace rpc{ namespace json{

struct ad_invoke_request_handler
{
  template<typename T, typename TM, typename R>
  void operator() (T& t, TM& tm, R params, int id)
  {
    if ( tm.get_aspect().template get<_ids_>().has(id) )
    {
      tm.get_aspect().template get<_invalid_id_>()( t, tm, params, id );
      return;
    }
    
    typedef typename TM::aspect::template advice_cast<_request_type_>::type request_type;
    typedef typename TM::aspect::template advice_cast<_request_json_>::type request_json;
    
    request_type request;

    tm.get_aspect().template get<_ids_>().push(id);

    try
    {
      if ( !tm.get_aspect().template get<_deserialize_params_>()(t, tm, request_json(), request, params ) )
        return;
    }
    catch(const ::fas::json::json_error& e)
    {
      // id освобождается при отправки сообщения об ошибке
      tm.get_aspect().template get< _deserialize_error_ >()( t, tm, ( e.message(params) ), id );
      return;
    }
    
    
    tm.get_aspect().template get<_request_>()(t, request, id);
  }
};


}}}

#endif
