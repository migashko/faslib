#ifndef FAS_JSONRPC_METHOD_AD_PARSE_REQUEST_HPP
#define FAS_JSONRPC_METHOD_AD_PARSE_REQUEST_HPP

#include <fas/jsonrpc/tags.hpp>
#include <fas/adv/ad_aspect_select.hpp>

namespace fas{ namespace jsonrpc{ 

struct ad_parse_request
{
  template<typename T, typename TM, typename R>
  void operator()(T& t, TM& tm, R r, int id)
  {
     
    typedef typename switch_by_tag_t<_deserializer_>::template select_t< TM, T >::type::aspect::template advice_cast<_deserializer_>::type deserializer;
    typedef typename TM::request_value_type request_value_type;
    typedef typename TM::request_json_type request_json_type;

    try
    {
      request_value_type value;
      deserializer()(request_json_type(), value, r );
      tm.get_aspect().template get<_request_handler_>()(t, tm, value, id); 
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
