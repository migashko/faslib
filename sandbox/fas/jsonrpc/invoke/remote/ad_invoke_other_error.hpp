#ifndef FAS_JSONRPC_INVOKE_AD_INVOKE_OTHER_ERROR_HPP
#define FAS_JSONRPC_INVOKE_AD_INVOKE_OTHER_ERROR_HPP

#include <fas/jsonrpc/method/tags.hpp>
#include <fas/jsonrpc/invoke/tags.hpp>


namespace fas{ namespace jsonrpc{

struct ad_invoke_other_error
{
  template<typename T, typename RP>
  void operator()(T& t, RP error )
  {

  }
};


}}

#endif
