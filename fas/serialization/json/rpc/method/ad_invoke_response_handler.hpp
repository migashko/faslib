#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_AD_INVOKE_RESPONSE_HANDLER_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_AD_INVOKE_RESPONSE_HANDLER_HPP

#include <fas/serialization/json/rpc/method/tags.hpp>

namespace fas{ namespace json{ namespace rpc{ namespace method{

struct ad_invoke_response_handler
{
  template<typename T, typename TM, typename RT>
  void operator() (T& t, TM& tm, const RT& response_value, int id)
  {
    if ( !tm.get_aspect().template get<_id_>().has(id) )
    {
      // зафигачить исключение 
    }
    
    tm.get_aspect().template get<_id_>().pop(id);
    
    typedef typename TM::aspect
                       ::template advice_cast<_response_buffer_>::type
                       ::template outgoing_buffer<T, TM>::type
                       ::initial_range_type 
      initial_range_type;
    
    typedef typename TM::aspect::template advice_cast<_invoke_response_json_>::type::json_type response_json_type;
    
    /*initial_range_type r = */tm.get_aspect().template get<_outgoing_serialize_>()
      ( 
        t, tm,
        response_json_type(),
        response_value,
        tm.get_aspect().template get<_response_buffer_>()(t, tm).get_initial_range()
      );
      
    // tm.get_aspect().template get<_output_>()(t, tm, r);
    t.get_aspect().template get<_outgoing_result_>()(t, tm.get_aspect().template get<_response_buffer_>()(t, tm).get_range(), id);
  }
};


}}}}

#endif

