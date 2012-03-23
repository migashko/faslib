#ifndef FAS_JSONRPC_METHOD_AD_REQUEST_HANDLER_HPP
#define FAS_JSONRPC_METHOD_AD_REQUEST_HANDLER_HPP

#include <fas/jsonrpc/tags.hpp>


namespace fas{ namespace jsonrpc{ 

struct ad_request_handler
{
  template<typename T, typename TM>
  void operator()(T& t, TM& tm, const typename TM::request_value_type& v, int id)
  {
    try
    {
      // TODO: сделать проверку ids
      tm.get_aspect().template get<_request_>()(t, v, id);
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
