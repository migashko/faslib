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
#include <fas/jsonrpc/method/local/notify.hpp>
#include <fas/jsonrpc/method/local/error.hpp>
#include <fas/range.hpp>

namespace ajr = ::fas::jsonrpc;
namespace aj = ::fas::json;

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
  t.get_aspect().template get< ajr::_output_ >().buffer.clear();
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
  clear(t);
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
  ajr::local::request< request_handler, request_handler::params_type, aj::array<aj::integer> >,
  ajr::local::result< int, aj::integer > 
>::type request_aspect;

UNIT(request, "")
{
  using namespace ::fas::testing;
  
  ajr::method<request_aspect> n;

  std::string jsonstring = "[1,2]";

  garbage(t, "garbage");
  n.get_aspect().get< ajr::local::_parse_request_>()( t, n, fas::range(jsonstring), 42 );
  t << equal<expect>( 3, n.get_aspect().get< ajr::_request_>().result ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"result\":3,\"id\":42}" ) << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  clear(t);
}

struct user_error
  : ajr::custom_error
{
  // int ;
  int foo;
  std::string bar;
  
  user_error()
    : ajr::custom_error( 44, "User Error" )
    , foo(41)
    , bar("bar")
  {
  }
};

FAS_NAME(data);
FAS_NAME(foo);
FAS_NAME(bar);

struct user_error_json: aj::object< fas::type_list_n<
  ajr::custom_error_json::target,
  aj::member< n_data, aj::object< fas::type_list_n<
    aj::member< n_foo, aj::attr< user_error, int, &user_error::foo, aj::integer > >,
    aj::member< n_bar, aj::attr< user_error, std::string, &user_error::bar, aj::string > >
  >::type > >
>::type > {};

struct request_handler_error
{
  request_handler_error() {}
  
  template<typename T, typename M>
  void operator()( T& t, M& m, int params, int id)
  {
    if ( params == 1 )
      m.error(t, m, ajr::error_code::invalid_params, id );
    else if ( params == 2 )
      m.error(t, m, 33, "Error33", id );
    else if ( params == 3 )
      m.error(t, m, user_error(), id );
    
  }
};

struct request_error_aspect: fas::type_list_n<
  ajr::local::request< request_handler_error, int , aj::integer >,
  ajr::local::error< user_error, user_error_json >
>::type {};

UNIT(request_error, "")
{
  using namespace ::fas::testing;

  ajr::method<request_error_aspect> n;

  std::string jsonstring = "1";
  garbage(t, "garbage");
  n.get_aspect().get< ajr::local::_parse_request_>()( t, n, fas::range(jsonstring), 42 );
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32602,\"message\":\"Invalid params.\"},\"id\":42}" )
    << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  clear(t);

  jsonstring = "2";
  garbage(t, "garbage");
  n.get_aspect().get< ajr::local::_parse_request_>()( t, n, fas::range(jsonstring), 42 );
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":33,\"message\":\"Error33\"},\"id\":42}" )
    << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
    
  clear(t);

  jsonstring = "3";
  garbage(t, "garbage");
  n.get_aspect().get< ajr::local::_parse_request_>()( t, n, fas::range(jsonstring), 42 );
  
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":44,\"message\":\"User Error\",\"data\":{\"foo\":41,\"bar\":\"bar\"}},\"id\":42}" )
    << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
    
  clear(t);

}


BEGIN_SUITE(method_suite, "json-rpc method suite")
  ADD_UNIT(notify)
  ADD_UNIT(request)
  ADD_UNIT(request_error)
  
  ADD_VALUE_ADVICE( ajr::_buffer_, std::string )
  ADD_ADVICE( ajr::_output_, ad_output )
  
  ADD_ASPECT( ajr::invoke_aspect )
  ADD_ASPECT( ajr::outgoing_aspect )
  ADD_ASPECT( ajr::inbound_aspect )
END_SUITE(method_suite)
