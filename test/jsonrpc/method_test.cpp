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
#include <fas/jsonrpc/method/remote/notify.hpp>
#include <fas/jsonrpc/method/remote/request.hpp>
#include <fas/jsonrpc/method/remote/result.hpp>
#include <fas/jsonrpc/method/remote/error.hpp>
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
  n.get_aspect().template get< ajr::local::_parse_notify_>()( t, n, fas::range(jsonstring) );
  t << equal<expect>( 3, n.get_aspect().template get< ajr::local::_notify_>().result ) << FAS_TESTING_FILE_LINE;
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
    m.result( t, result, id );
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
  n.get_aspect().template get< ajr::local::_parse_request_>()( t, n, fas::range(jsonstring), 42 );
  t << equal<expect>( 3, n.get_aspect().template  get< ajr::local::_request_>().result ) << FAS_TESTING_FILE_LINE;
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


// struct aaa{};

FAS_NAME(data);
FAS_NAME(foo);
FAS_NAME(bar);

typedef aj::object< fas::type_list_n<
  ajr::custom_error_json::target,
  aj::member< n_data, aj::object< fas::type_list_n<
    aj::member< n_foo, aj::attr< user_error, int, &user_error::foo, aj::integer > >,
    aj::member< n_bar, aj::attr< user_error, std::string, &user_error::bar, aj::string > >
  >::type > >
>::type > user_error_json;

struct request_handler_error
{
  request_handler_error() {}
  
  template<typename T, typename M>
  void operator()( T& t, M& m, int params, int id)
  {
    if ( params == 1 )
      m.error(t, ajr::error_code::invalid_params, id );
    else if ( params == 2 )
      m.error(t, 33, "Error 33", id );
    else if ( params == 3 )
      m.error(t, user_error(), id );
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
  n.get_aspect().template get< ajr::local::_parse_request_>()( t, n, fas::range(jsonstring), 42 );
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32602,\"message\":\"Invalid params.\"},\"id\":42}" )
    << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  clear(t);

  jsonstring = "2";
  garbage(t, "garbage");
  n.get_aspect().template get< ajr::local::_parse_request_>()( t, n, fas::range(jsonstring), 42 );
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":33,\"message\":\"Error 33\"},\"id\":42}" )
    << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
    
  clear(t);

  jsonstring = "3";
  garbage(t, "garbage");
  n.get_aspect().template get< ajr::local::_parse_request_>()( t, n, fas::range(jsonstring), 42 );
  
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":44,\"message\":\"User Error\",\"data\":{\"foo\":41,\"bar\":\"bar\"}},\"id\":42}" )
    << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
    
  clear(t);

}

FAS_NAME(notify);
  
typedef ajr::method< fas::type_list_n<
    ajr::name<n_notify>,
    ajr::remote::notify< 
      std::string, 
      aj::string
    > 
>::type > notify_method;

UNIT(remote_notify, "")
{
  using namespace ::fas::testing;
  
  notify_method n;
  garbage(t, "garbage");
  n.notify(t, "1" );
  //n.get_aspect().get< ajr::local::_parse_request_>()( t, n, fas::range(jsonstring), 42 );
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"method\":\"notify\",\"params\":\"1\"}" )
    << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  clear(t);

}

FAS_NAME(request);

struct result_handler
{
  int result;
  result_handler(): result(0){}
  
  template<typename T, typename M>
  void operator()( T&, M&, int params, int id)
  {
    result = params;
  }
};
  
typedef ajr::method< fas::type_list_n<
    ajr::name<n_request>,
    ajr::remote::request< std::string, aj::string >,
    ajr::remote::result< result_handler, int, aj::integer >
>::type > request_method;

UNIT(remote_request, "")
{
  using namespace ::fas::testing;
  
  request_method n;
  garbage(t, "garbage");
  ajr::id_t id = n.request(t, "1" );
  t << equal<expect>( id, 1 ) << FAS_TESTING_FILE_LINE << std::endl << id;
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"method\":\"request\",\"params\":\"1\",\"id\":1}" )
    << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  clear(t);
  
  id = n.request(t, "2" );
  t << equal<expect>( id, 2 ) << FAS_TESTING_FILE_LINE << std::endl << id;
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"method\":\"request\",\"params\":\"2\",\"id\":2}" )
    << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  clear(t);
  
  
  n.get_aspect().template get< ajr::remote::_parse_result_>()( t, n, fas::range("1"), 1 );
  t << equal<expect>( n.get_aspect().template get< ajr::remote::_result_>().result, 1 ) << FAS_TESTING_FILE_LINE << std::endl;

  // invalid id
  n.get_aspect().template get< ajr::remote::_parse_result_>()( t, n, fas::range("2"), 1 );
  t << equal<expect>( n.get_aspect().template get< ajr::remote::_result_>().result, 1 ) << FAS_TESTING_FILE_LINE << std::endl;

  n.get_aspect().template get< ajr::remote::_parse_result_>()( t, n, fas::range("2"), 2 );
  t << equal<expect>( n.get_aspect().template get< ajr::remote::_result_>().result, 2 ) << FAS_TESTING_FILE_LINE << std::endl;

  // invalid id
  n.get_aspect().template get< ajr::remote::_parse_result_>()( t, n, fas::range("3"), 2 );
  t << equal<expect>( n.get_aspect().template get< ajr::remote::_result_>().result, 2 ) << FAS_TESTING_FILE_LINE << std::endl;
}

struct error_handler
{
  int error;
  error_handler(): error(0){}
  
  template<typename T, typename M>
  void operator()( T&, M&, const ajr::custom_error& err, int id)
  {
    error = err.code;
  }
};

typedef ajr::method< fas::type_list_n<
    ajr::name<n_request>,
    ajr::remote::request< std::string, aj::string >,
    ajr::remote::error< error_handler>
>::type > error_method;

UNIT(remote_error, "")
{
  using namespace ::fas::testing;
  
  error_method n;
  garbage(t, "garbage");
  ajr::id_t id = n.request(t, n, "1" );
  t << equal<expect>( id, 1 ) << FAS_TESTING_FILE_LINE << std::endl << id;
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"method\":\"request\",\"params\":\"1\",\"id\":1}" )
    << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  clear(t);
  
  id = n.request(t, n, "2" );
  t << equal<expect>( id, 2 ) << FAS_TESTING_FILE_LINE << std::endl << id;
  t << equal<expect>( buffer(t), "{\"jsonrpc\":\"2.0\",\"method\":\"request\",\"params\":\"2\",\"id\":2}" )
    << FAS_TESTING_FILE_LINE << std::endl << buffer(t);
  clear(t);
  
  
  n.get_aspect().template get< ajr::remote::_parse_error_>()( t, n, fas::range("2"), 1 );
  t << equal<expect>( n.get_aspect().template get< ajr::remote::_error_>().error, 1 ) << FAS_TESTING_FILE_LINE << std::endl;

  // invalid id
  n.get_aspect().template get< ajr::remote::_parse_error_>()( t, n, fas::range("2"), 1 );
  t << equal<expect>( n.get_aspect().template get< ajr::remote::_error_>().error, 1 ) << FAS_TESTING_FILE_LINE << std::endl;

  n.get_aspect().template get< ajr::remote::_parse_error_>()( t, n, fas::range("2"), 2 );
  t << equal<expect>( n.get_aspect().template get< ajr::remote::_error_>().error, 2 ) << FAS_TESTING_FILE_LINE << std::endl;

  // invalid id
  n.get_aspect().template get< ajr::remote::_parse_error_>()( t, n, fas::range("3"), 2 );
  t << equal<expect>( n.get_aspect().template get< ajr::remote::_error_>().error, 2 ) << FAS_TESTING_FILE_LINE << std::endl;
}



BEGIN_SUITE(method_suite, "json-rpc method suite")
  ADD_UNIT(notify)
  ADD_UNIT(request)
  ADD_UNIT(request_error)
  ADD_UNIT(remote_notify)
  ADD_UNIT(remote_request)
  ADD_VALUE_ADVICE( ajr::_buffer_, std::string )
  ADD_ADVICE( ajr::_output_, ad_output )
  
  ADD_ASPECT( ajr::invoke_aspect )
  ADD_ASPECT( ajr::outgoing_aspect )
  ADD_ASPECT( ajr::inbound_aspect )
END_SUITE(method_suite)
