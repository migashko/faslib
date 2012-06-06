#ifndef FAS_SERIALIZATION_JSON_RPC_METHOD_TAGS_HPP
#define FAS_SERIALIZATION_JSON_RPC_METHOD_TAGS_HPP

namespace fas{ namespace json{ namespace rpc{ /*namespace method{*/

struct _name_;

struct _id_;

// Сериализатор и десериализатор для метода 
struct _deserializer_;
struct _serializer_;

// value_json контейнеры
struct _invoke_request_;
struct _invoke_request_json_;
struct _invoke_response_;
struct _invoke_response_json_;
struct _invoke_notify_;

struct _call_request_;
struct _call_response_;
struct _call_notify_;

// Обработчики
struct _request_;
struct _response_;
struct _notify_;

struct _select_advice_;

// Десериализует и сериализует 
struct _incoming_deserialize_;
struct _outgoing_serialize_;

struct _outgoing_buffer_;
struct _response_buffer_;
// Обрабочики входящих запросов
struct _invoke_request_handler_;
struct _invoke_response_handler_;

struct _response_object_;
struct _response_object_json_;

// обработчик ответа на запрос 
struct _outgoing_result_;

struct _output_;  

}}}/*}*/

#endif
