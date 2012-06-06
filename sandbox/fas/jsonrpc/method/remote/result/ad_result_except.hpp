#ifndef FAS_JSONRPC_METHOD_REMOTE_RESULT_AD_RESULT_EXCEPT_HPP
#define FAS_JSONRPC_METHOD_REMOTE_RESULT_AD_RESULT_EXCEPT_HPP

#include <fas/jsonrpc/types.hpp>

namespace fas{ namespace jsonrpc{ namespace remote{

struct ad_result_except
{
  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&, const std::exception& , id_t id)
  {
    
  }

  template<typename T, typename M, typename V>
  void operator() (T& t, M&, V&, id_t id)
  {
  }
};

}}}

#endif
