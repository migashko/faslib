#ifndef FAS_JSONRPC_METHOD_AD_NOTIFY_HANDLER_HPP
#define FAS_JSONRPC_METHOD_AD_NOTIFY_HANDLER_HPP

#include <fas/jsonrpc/tags.hpp>


namespace fas{ namespace jsonrpc{ 

struct ad_notify_handler
{
  template<typename T, typename TM>
  void operator()(T& t, TM& tm, const typename TM::notify_value_type& v)
  {
    try
    {
      tm.get_aspect().template get<_notify_>()(t, v);
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
