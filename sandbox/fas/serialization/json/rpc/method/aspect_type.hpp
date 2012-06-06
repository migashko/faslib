#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_ASPECT_TYPE_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_ASPECT_TYPE_HPP

#include <fas/serialization/json/rpc/method/tags.hpp>

#include <fas/serialization/json/rpc/method/ad_id.hpp>
#include <fas/serialization/json/rpc/method/ad_invoke_request_handler.hpp>
#include <fas/serialization/json/rpc/method/ad_incoming_deserialize.hpp>

#include <fas/serialization/json/rpc/method/ad_response_buffer.hpp>
#include <fas/serialization/json/rpc/method/ad_invoke_response_handler.hpp>
#include <fas/serialization/json/rpc/method/ad_outgoing_serialize.hpp>
#include <fas/serialization/json/rpc/method/ad_outgoing_buffer.hpp>

#include <fas/serialization/json/rpc/method/invoke_request.hpp>
#include <fas/serialization/json/rpc/method/request.hpp>
#include <fas/serialization/json/rpc/method/invoke_response.hpp>
//#include <fas/serialization/json/rpc/method/value_json.hpp>


#include <fas/aop/stub.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/type_list/type_list_n.hpp>

namespace fas{ namespace json{ namespace rpc{ namespace method{

typedef typename type_list_n<
  ::fas::stub< _output_ >,
  advice< _id_, ad_id<> >,
  advice< _response_buffer_, ad_response_buffer >,
  advice< _invoke_request_handler_, ad_invoke_request_handler >,
  advice< _invoke_response_handler_, ad_invoke_response_handler >,
  advice< _incoming_deserialize_, ad_incoming_deserialize >,
  advice< _outgoing_serialize_, ad_outgoing_serialize >
>::type advice_list;

typedef ::fas::aspect<advice_list> aspect_type;

/*
 ADD_ADVICE( ::fas::json::rpc::method::_deserializer_, ::fas::json::deser::deserializer<> )
 ADD_ADVICE( ::fas::json::rpc::method::_serializer_, ::fas::json::ser::serializer<> )
 ADD_ADVICE( ::fas::json::rpc::method::_outgoing_buffer_, ::fas::json::rpc::method::ad_outgoing_buffer<> )
*/

}}}}

#endif
