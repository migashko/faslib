#ifndef FAS_RPC_JSON_TAGS_HPP
#define FAS_RPC_JSON_TAGS_HPP

namespace fas{ namespace rpc{ namespace json{

// Группы
struct _clear_;
struct _initialize_;
struct _dispose_;

// Пользовательские 
struct _name_;
struct _request_;
struct _request_type_;
struct _request_json_;
struct _response_type_;
struct _response_json_;

struct _notify_;
struct _notify_type_;
struct _notify_json_;

// Аспектные
struct _ids_;
struct _call_ids_;

struct _error_;
struct _invalid_id_;
struct _invalid_request_;
struct _not_impl_;
struct _deserialize_error_;
struct _parse_error_;

struct _invoke_request_handler_;
struct _invoke_notify_handler_;
struct _invoke_result_handler_;
struct _invoke_error_handler_;



struct _serializer_;
struct _deserializer_;

struct _switch_deserialize_;
struct _deserialize_params_;


  
}}}

#endif
