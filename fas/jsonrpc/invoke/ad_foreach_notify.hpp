#ifndef FAS_JSONRPC_TAGS_HPP
#define FAS_JSONRPC_TAGS_HPP

namespace fas{ namespace jsonrpc{

struct _jsonrpc_;
struct _input_;
struct _output_;
struct _invoke_;
struct _context_;
struct _notify_value_;
struct _notify_json_;
struct _notify_handler_;
struct _request_handler_;

struct _request_value_;
struct _request_json_;
struct _result_value_;
struct _result_json_;

struct _parse_notify_;
struct _parse_request_;
struct _send_result_;

struct _method_;

struct _outgoing_buffer_;
struct _outgoing_buffer_manager_;
  
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

struct _send_error_;
struct _invalid_id_;
struct _invalid_request_;
struct _method_not_found_;
struct _not_impl_;
struct _deserialize_error_;
struct _parse_error_;

struct _invoke_request_handler_;
struct _invoke_notify_handler_;
struct _invoke_result_handler_;
struct _invoke_error_handler_;

struct _process_;
struct _process_object_;

struct _serializer_;
struct _deserializer_;
struct _parser_;

struct _switch_deserialize_;
struct _deserialize_params_;
 
}}

#endif
