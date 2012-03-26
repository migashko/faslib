#ifndef FAS_JSONRPC_METHOD_AD_SEND_RESULT_NULL_HPP
#define FAS_JSONRPC_METHOD_AD_SEND_RESULT_NULL_HPP

#include <fas/jsonrpc/outgoing/tags.hpp>
#include <fas/jsonrpc/method/tags.hpp>
//#include <fas/jsonrpc/response_object.hpp>
//#include <fas/jsonrpc/response_object_json.hpp>
//#include <fas/adv/ad_aspect_select.hpp>
//#include <fas/range/range.hpp>

namespace fas{ namespace jsonrpc{ 
  
  /*
struct ad_send_result_null
{
  template<typename T, typename M>
  void operator()(T& t, M& , const void* result, int id)
  {
    typedef result_object<const void*> result_object_type;
    typedef result_object_json<result_object_type, const void*, aj::null> json_object_type;
    
    t.get_aspect().template get<_send_>()( t, 
      json_object_type(), 
      result_object_type(0, id) 
    );
  }
};
*/


}}

#endif
