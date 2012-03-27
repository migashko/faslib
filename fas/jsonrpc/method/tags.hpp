#ifndef FAS_JSONRPC_METHOD_TAGS_HPP
#define FAS_JSONRPC_METHOD_TAGS_HPP

namespace fas{ namespace jsonrpc{

struct _name_;
struct _method_id_;
struct _notify_;
struct _request_;
struct _context_;
struct _remote_result_;

struct _request_error_;
struct _notify_error_;

struct _send_request_error_;
struct _send_notify_error_;

struct _send_notify_;

struct _parse_notify_;
struct _parse_request_;

struct _parse_response_;
struct _parse_error_;

struct _send_result_;
struct _send_request_;

struct _request_value_;
struct _request_json_;

struct _result_value_;
struct _result_json_;

struct _request_handler_;
struct _notify_handler_;
struct _response_handler_;

}}

#endif
