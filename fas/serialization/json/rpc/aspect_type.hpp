#ifndef FAS_SERIALIZATION_JSON_ASPECT_TYPE_HPP
#define FAS_SERIALIZATION_JSON_ASPECT_TYPE_HPP

#include <fas/serialization/json/deser/deserializer.hpp>
#include <fas/serialization/json/rpc/tags.hpp>
#include <fas/serialization/json/rpc/ad_invoke.hpp>


#include <fas/serialization/json/rpc/method/method_base.hpp>
#include <fas/serialization/json/rpc/method/name.hpp>
#include <fas/serialization/json/rpc/method/invoke_request.hpp>
#include <fas/serialization/json/rpc/method/request.hpp>
#include <fas/serialization/json/rpc/method/invoke_response.hpp>
#include <fas/serialization/json/rpc/method/value_json.hpp>
#include <fas/serialization/json/rpc/method/ad_outgoing_buffer.hpp>



#include <fas/serialization/json/deser/deserializer.hpp>
#include <fas/serialization/json/ser/serializer.hpp>

#include <fas/type_list/type_list_n.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>


namespace fas{ namespace json{ namespace rpc{

typedef type_list_n<
  advice<_invoke_, ad_invoke>,
  advice<_invoke_method_, ad_invoke_method>,
  advice<_invoke_exec_, ad_invoke_exec>,
  advice<_invoke_batch_, ad_invoke_batch>,
  advice<_outgoing_result_, ad_outgoing_result>,
  
  advice< _serializer_, ::fas::json::ser::serializer<> >,
  advice< _deserializer_, deser::deserializer<> >,
  advice< _outgoing_buffer_, method::ad_outgoing_buffer<> >
>::type advice_list;

  /*ADD_ADVICE( ::fas::json::rpc::method::_deserializer_, ::fas::json::deser::deserializer<> )
  ADD_ADVICE( ::fas::json::rpc::method::_serializer_, ::fas::json::ser::serializer<> )
  ADD_ADVICE( ::fas::json::rpc::method::_outgoing_buffer_, ::fas::json::rpc::method::ad_outgoing_buffer<> )
  */


typedef aspect<advice_list> aspect_type;
  
}}}

#endif
