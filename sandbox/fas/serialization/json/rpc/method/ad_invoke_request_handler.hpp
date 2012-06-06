#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_AD_INVOKE_REQUEST_HANDLER_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_AD_INVOKE_REQUEST_HANDLER_HPP

#include <fas/serialization/json/rpc/method/tags.hpp>

namespace fas{ namespace json{ namespace rpc{ namespace method{


struct ad_invoke_request_handler
{
  template<typename T, typename TM, typename R>
  void operator() (T& t, TM& tm, R params, int id)
  {
    if ( tm.get_aspect().template get<_id_>().has(id) )
    {
      // отправить ошибку? if (_check_) return
    }
    
    typedef typename TM::aspect::template advice_cast<_invoke_request_>::type::value_type request_value_type;
    typedef typename TM::aspect::template advice_cast<_invoke_request_json_>::type::json_type request_json_type;
    
    typedef typename TM::aspect::template advice_cast<_invoke_response_>::type::value_type response_value_type;
    typedef typename TM::aspect::template advice_cast<_invoke_response_json_>::type::json_type response_json_type;

    
    tm.get_aspect().template get<_id_>().push(id);
    
    request_value_type request_value;
    
    tm.get_aspect().template get<_incoming_deserialize_>()
      ( 
        t, tm,
        //tm.get_aspect().template get<_invoke_request_>(), 
        request_json_type(),
        request_value,
        params
      );
      
    /** TODO: продумать стратегии
     *    1. Для sync создаем шаблонный response объект и его сериализуем стразу 
     *    2. Для !sync сериализуем объект а затем создаем response-range объект и сериализуем его (пока делаем только этот вариант)
     *    3. Для малых объектов создаем шаблонный response, копируем объект и сериализуем его 
     */
    response_value_type response_value;
    bool sync = tm.get_aspect().template get<_request_>()(t, 
      request_value,
      id, 
      response_value
    );
    
    if ( sync )
      tm.get_aspect().template get<_invoke_response_handler_>()(t, tm, response_value, id);
  }
};


}}}}

#endif
