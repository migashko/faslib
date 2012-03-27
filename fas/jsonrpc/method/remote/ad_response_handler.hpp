#ifndef FAS_JSONRPC_METHOD_AD_RESPONSE_HANDLER_HPP
#define FAS_JSONRPC_METHOD_AD_RESPONSE_HANDLER_HPP

#include <fas/jsonrpc/error/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>


namespace fas{ namespace jsonrpc{ 

struct ad_response_handler
{
  template<typename T, typename M, typename V>
  void operator()(T& t, M& m, const V& v, int id)
  {
    try
    {
      // TODO: сделать проверку ids
      m.get_aspect().template get<_remote_result_>()(t, m, v, id);
    }
    catch(const std::exception& /*e*/)
    {
      //?? t.get_aspect().template get<_internal_error_>()(t, id);
      // server error
    }
    catch(...)
    {
      //?? t.get_aspect().template get<_internal_error_>()(t, id);
      // server error
    }
  }
};


}}

#endif
