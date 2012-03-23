#ifndef FAS_JSONRPC_AD_PROCESS_RESPONSE_HPP
#define FAS_JSONRPC_AD_PROCESS_RESPONSE_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/jsonrpc/response_object.hpp>
#include <fas/jsonrpc/response_object_json.hpp>
#include <fas/adv/ad_aspect_select.hpp>
#include <fas/range/range.hpp>

namespace fas{ namespace jsonrpc{ 
  
struct ad_process_response
{
  template<typename T, typename TM>
  void operator()(T& t, TM& tm, const typename TM::result_value_type& result, int id)
  {
     
    typedef typename switch_by_tag_t<_serializer_>::template select_t< TM, T >::type::aspect::template advice_cast<_serializer_>::type serializer;
    typedef typename TM::result_value_type result_value_type;
    typedef typename TM::result_json_type result_json_type;
    
    typedef response_object< result_value_type > response_object_type;
    typedef response_object_json< result_json_type, response_object_type > response_object_json_type;

    try
    {
      std::string tmp;
      //&response_object_type::result;
      serializer()(response_object_json_type(), response_object_type(result, id), init_range(tmp) );
      
      /*
      int *a;
      int &b = *a;
      */
      
      std::cout << std::endl << tmp << std::endl;
      //tm.get_aspect().template get<_request_handler_>()(t, tm, value, id); 
    }
    catch(const std::exception& /*e*/)
    {
      // server error
    }
    catch(...)
    {
      // server error
    }
  }
};


}}

#endif
