#ifndef FAS_JSONRPC_ASPECT_HPP
#define FAS_JSONRPC_ASPECT_HPP

#include <fas/jsonrpc/aspect_type.hpp>

namespace fas{ namespace jsonrpc{ 

/*
0     * - input
      |
1   _inbound_
      |    |----> _parse_error_
      |
2   _parse_incoming_
      |    |----> _invalid_request_ -->
      |    |----> _parse_error_ --> ???
      |    |----> _parse_array_ -->
      |
3   _parse_object_
      |     |----> _invalid_request_
      |
4   _process_object_
            |     |
4.1         |  _invoke_notify_ [[ for_each< _notify_group_ > ]]
            |     |      |
            |     |      |-------> _notify_not_found_ --> _send_error_( code::method_not_found ) -->
            |     |
            |   method::parse_notify()
            |     |
            |     X
            |
          _invoke_request_
            |-------> _request_not_found_ --> _send_error_( code::method_not_found )
            |
          _parse_request_
            |         |------> _invalid_request_ -->
            |
          _request_handler_
            |         |-------> _request_except_  --> _send_error_( code::internal_error ) -->
            |
          _request_
            |
            |
          method::result(...)
            |
          _request_result_
            |
            -------> _send_result_
            
            _invoke_result_

                  _invoke_error_

                  _invoke_other_error_


            |  _parse_notify_
            |     |      |-------> _invalid_request_ -->
            |     |
            |  _notify_handler_
            |     |      |-------> _notify_except_  --> _send_error_( code::internal_error ) -->
            |     |
            |  _notify_
            |     |
            |     X

*/
  
struct aspect: aspect_type { };
  
}}

#endif
