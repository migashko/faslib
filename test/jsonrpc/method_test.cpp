#include <fas/testing.hpp>
#include <fas/typemanip/tstring.hpp>

#include <fas/serialization/json/meta.hpp>

#include <fas/jsonrpc/invoke/invoke_aspect.hpp>
#include <fas/jsonrpc/inbound/inbound_aspect.hpp>
#include <fas/jsonrpc/outgoing/outgoing_aspect.hpp>


#include <fas/jsonrpc/method/method.hpp>
#include <fas/jsonrpc/method/name.hpp>
#include <fas/jsonrpc/method/local/request.hpp>
#include <fas/jsonrpc/method/local/result.hpp>
/*
#include <fas/jsonrpc/method/remote/remote_notify.hpp>
#include <fas/jsonrpc/method/remote/remote_request.hpp>
#include <fas/jsonrpc/method/remote/remote_result.hpp>
*/
#include <fas/jsonrpc/method/local/notify.hpp>
#include <fas/jsonrpc/method/local/error.hpp>
/*
#include <fas/jsonrpc/outgoing/outgoing_aspect.hpp>
#include <fas/jsonrpc/json/json_aspect.hpp>
#include <fas/jsonrpc/error/error_aspect.hpp>
#include <fas/jsonrpc/error/json/custom_error.hpp>
#include <fas/jsonrpc/invoke/invoke_aspect.hpp>
*/
#include <fas/range.hpp>

namespace ajr = ::fas::jsonrpc;
namespace aj = ::fas::json;

/*
struct method_request
{
  typedef int params_type[2];
  int result;
  method_request(): result(-1) {}
  template<typename T, typename M>
  void operator()( T&t, M& m, const int params[2], int id)
  {
    result = params[0] + params[1];
    m.result( t, m, result, id );
  }
};

struct method_notify
{
  typedef int params_type[2];
  int result;
  method_notify(): result(-1)
  {}
  
  template<typename T, typename M>
  void operator()( T&t, M& m, const int params[2] )
  {
    result = params[0] + params[1];
  }
};


FAS_NAME(method)

typedef ajr::method<
  fas::type_list_n<
    ajr::name<n_method>,
    ajr::notify< method_notify, method_notify::params_type, aj::array<aj::integer> >
  >::type
> method_notify_test;
*/

struct ad_output
{
  std::string buffer;
  template<typename T, typename R>
  void operator()(T& t, R r)
  {
    buffer += t.get_aspect().template get< ajr::_buffer_ >();
  }
};

template<typename T>
inline void clear(T& t)
{
  t.get_aspect().template get< ajr::_buffer_ >().buffer.clear();
}


template<typename T>
inline std::string buffer(T& t)
{
  return t.get_aspect().template get< ajr::_output_>().buffer;
}

template<typename T>
inline void garbage(T& t, std::string data)
{
  t.get_aspect().template get< ajr::_buffer_ >() = data;
}


struct notify_handler
{
  typedef int params_type[2];
  int result;
  notify_handler(): result(-1) {}

  template<typename T, typename M>
  void operator()( T&t, M& m, const int params[2] )
  {
    result = params[0] + params[1];
  }
};


typedef ajr::local::notify< notify_handler, notify_handler::params_type, aj::array<aj::integer> > notify_aspect;


UNIT(notify, "")
{
  using namespace ::fas::testing;
  
  ajr::method<notify_aspect> n;

  std::string jsonstring = "[1,2]";

  garbage(t, "garbage");
  n.get_aspect().get< ajr::local::_parse_notify_>()( t, n, fas::range(jsonstring) );
  t << equal<expect>( 3, n.get_aspect().get< ajr::_notify_>().result ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( buffer(t), "" ) << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
}


struct request_handler
{
  typedef int params_type[2];
  int result;
  request_handler(): result(-1) {}
  template<typename T, typename M>
  void operator()( T&t, M& m, const int params[2], int id)
  {
    result = params[0] + params[1];
    m.result( t, m, result, id );
  }
};

typedef fas::type_list_n<
  ajr::request< request_handler, request_handler::params_type, aj::array<aj::integer> >,
  ajr::local::result< int, aj::integer > 
>::type request_aspect;
/*
typedef ajr::method<
  fas::type_list_n<
    ajr::name<n_method>,
    ajr::request< method_request, method_request::params_type, aj::array<aj::integer> >,
    ajr::result<int, aj::integer>
  >::type
> method_request_test;
*/

UNIT(request, "")
{
  using namespace ::fas::testing;
  
  ajr::method<request_aspect> n;

  std::string jsonstring = "[1,2]";

  garbage(t, "garbage");
  n.get_aspect().get< ajr::local::_parse_request_>()( t, n, fas::range(jsonstring), 42 );
  t << equal<expect>( 3, n.get_aspect().get< ajr::_request_>().result ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"result\":3,\"id\":42}" ) << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  

  /*
  method_request_test request;

  std::string jsonstring = "[1,2]";

  buffer(t, "garbage");
  request.get_aspect().get< ajr::_parse_request_>()( t, request, fas::range(jsonstring), 22 );
  t << equal<expect>( 3, request.get_aspect().get< ajr::_request_>().result ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( buffer(t), "" ) << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  */
  
  /*
   * std::string jsonstring = "[1,2]";
  method_test_request mtr;
  mtr.get_aspect().get<ajr::_parse_request_>()(t, mtr, fas::range(jsonstring), 1 ); 
  std::cout << "[" << t.get_aspect().template get< ajr::_buffer_>() << "]" << std::endl;
  t.get_aspect().template get< ajr::_buffer_>().clear();
  mtr.get_aspect().get<ajr::_parse_notify_>()(t, mtr, fas::range(jsonstring) );
  std::cout << "[" << t.get_aspect().template get< ajr::_buffer_>() << "]" << std::endl;
  mtr.get_aspect().get<ajr::_parse_response_>()(t, mtr, fas::range(jsonstring), 1 );
  std::cout << "[" << t.get_aspect().template get< ajr::_buffer_>() << "]" << std::endl;

  mtr.get_aspect().template get< ajr::_method_id_>().push(1);
  mtr.error( t, mtr, ajr::custom_error(-1, "my errror"), 1 );

  std::cout << "[" << t.get_aspect().template get< ajr::_buffer_>() << "]" << std::endl;
  
  mtr.get_aspect().template get< ajr::_method_id_>().push(1);
  mtr.error( t, mtr, 33, "my errror", 1 );

  std::cout << "[" << t.get_aspect().template get< ajr::_buffer_>() << "]" << std::endl;

  mtr.get_aspect().template get< ajr::_method_id_>().push(1);
  mtr.error( t, mtr, ajr::error_code::internal_error, 1 );

  std::cout << "[" << t.get_aspect().template get< ajr::_buffer_>() << "]" << std::endl;

  mtr.get_aspect().template get< ajr::_method_id_>().push(1);
  t.get_aspect().template get< ajr::_send_error_>()( t, 44, "message error" );

  std::cout << "[" << t.get_aspect().template get< ajr::_buffer_>() << "]" << std::endl;

  mtr.get_aspect().template get< ajr::_method_id_>().push(1);
  mtr.error( t, mtr, ajr::custom_error(ajr::error_code::internal_error), 1 );

  std::cout << "[[" << t.get_aspect().template get< ajr::_buffer_>() << "]]" << std::endl;
 */ 
}

BEGIN_SUITE(method_suite, "json-rpc method suite")
  ADD_UNIT(notify)
  ADD_UNIT(request)
  
  ADD_VALUE_ADVICE( ajr::_buffer_, std::string )
  ADD_ADVICE( ajr::_output_, ad_output )
  
  ADD_ASPECT( ajr::invoke_aspect )
  ADD_ASPECT( ajr::outgoing_aspect )
  ADD_ASPECT( ajr::inbound_aspect )
  
  
END_SUITE(method_suite)
