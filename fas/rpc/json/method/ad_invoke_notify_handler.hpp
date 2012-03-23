#ifndef FAS_RPC_JSON_METHOD_AD_INVOKE_NOTIFY_HANDLER_HPP
#define FAS_RPC_JSON_METHOD_AD_INVOKE_NOTIFY_HANDLER_HPP

#include <fas/rpc/json/tags.hpp>
#include <fas/serialization/json/except.hpp>

namespace fas{ namespace rpc{ namespace json{ 

struct ad_invoke_notify_handler
{
  template<typename T, typename TM, typename R>
  void operator() (T& t, TM& tm, R params)
  {
    typedef typename TM::aspect::template advice_cast<_notify_type_>::type notify_type;
    typedef typename TM::aspect::template advice_cast<_notify_json_>::type notify_json;
    
    notify_type request;

    try
    {
      tm.get_aspect().template get<_deserialize_params_>()
        (t, tm, notify_json(), request, params );
    }
    catch(const ::fas::json::json_error& e)
    {
      // id освобождается при отправки сообщения об ошибке
      tm.get_aspect().template get< _deserialize_error_ >()( t, tm, ( e.message(params) ) );
      return;
    }
    
    tm.get_aspect().template get<_notify_>()(t, request);
  }
};


}}}

#endif
