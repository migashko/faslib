#include <fas/jsonrpc/outgoing/outgoing_aspect.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/serialization/json/deserializer.hpp>
#include <fas/testing.hpp>
#include <fas/range.hpp>

namespace aj = ::fas::json;
namespace ajr = ::fas::jsonrpc;

template<typename T>
std::string buffer(T& t)
{
  return t.get_aspect().template get< ajr::_buffer_ >();
}

UNIT(outgoing_error, "")
{
  using namespace ::fas::testing;

  std::string jsonrpc;
  
  t.get_aspect().template get< ajr::_send_error_ >()( t, ajr::error_code::invalid_request );
  jsonrpc = buffer(t);
  t << equal<expect>( jsonrpc, "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32600,\"message\":\"Invalid Request.\"},\"id\":null}" ) << FAS_TESTING_FILE_LINE
    << std::endl << jsonrpc << std::endl;

  t.get_aspect().template get< ajr::_send_error_ >()( t, ajr::error_code::invalid_request, 1 );
  jsonrpc = buffer(t);
  t << equal<expect>( jsonrpc, "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32600,\"message\":\"Invalid Request.\"},\"id\":1}" ) << FAS_TESTING_FILE_LINE
    << std::endl << jsonrpc << std::endl;

  t.get_aspect().template get< ajr::_send_error_ >()( t, ajr::error_code::invalid_request, "Invalid Request 2.");
  jsonrpc = buffer(t);
  t << equal<expect>( jsonrpc, "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32600,\"message\":\"Invalid Request 2.\"},\"id\":null}" ) << FAS_TESTING_FILE_LINE
    << std::endl << jsonrpc << std::endl;

    
  t.get_aspect().template get< ajr::_send_error_ >()( t, ajr::error_code::invalid_request, "Invalid Request 2.", 2 );
  jsonrpc = buffer(t);
  t << equal<expect>( jsonrpc, "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32600,\"message\":\"Invalid Request 2.\"},\"id\":2}" ) << FAS_TESTING_FILE_LINE
    << std::endl << jsonrpc << std::endl;
}

UNIT(outgoing_custom_error, "")
{
  using namespace ::fas::testing;

  std::string jsonrpc;

  ajr::custom_error error1( ajr::error_code::parse_error );
  t.get_aspect().template get< ajr::_send_>()( t,
    ajr::error_notify_json< ajr::custom_error, ajr::custom_error_json >(),
    error1
  );

  jsonrpc = buffer(t);
  t << equal<expect>( jsonrpc, "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32700,\"message\":\"Parse error.\"},\"id\":null}" ) << FAS_TESTING_FILE_LINE
    << std::endl << jsonrpc << std::endl;

  ajr::custom_error error2( ajr::error_code::parse_error, "Parse error 2."  );
  t.get_aspect().template get< ajr::_send_>()( t,
    ajr::error_message_json<  ajr::error_message_object< ajr::custom_error >, ajr::custom_error, ajr::custom_error_json >(),
    ajr::error_message_object< ajr::custom_error>( error2, 3 )
  );

  jsonrpc = buffer(t);
  t << equal<expect>( jsonrpc, "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32700,\"message\":\"Parse error 2.\"},\"id\":3}" ) << FAS_TESTING_FILE_LINE
    << std::endl << jsonrpc << std::endl;
}
 
struct user_error
  : ajr::custom_error
{
  size_t position;
  std::string description;
  
  user_error(size_t position, std::string description)
    : ajr::custom_error( ajr::error_code::parse_error )
    , position(position)
    , description(description)
  {};
};

FAS_NAME(data)
FAS_NAME(position)
FAS_NAME(description)

typedef aj::object<
  fas::type_list_n<
    ajr::custom_error_json::target,
    aj::member< n_data,
      aj::object<
        fas::type_list_n<
          aj::member< n_position, aj::attr< user_error, size_t, &user_error::position, aj::integer > >,
          aj::member< n_description, aj::attr< user_error, std::string, &user_error::description, aj::string > >
        >::type
      >
    >
  >::type
> user_error_json;

UNIT(outgoing_user_error, "")
{
  using namespace ::fas::testing;
  std::string jsonrpc;

  const char jsonstring[] = "[1,2,},3,4,5]";
  try
  {
    aj::deserializer<> ds;
    int arr[3] = {0};
    ds( aj::array< aj::integer >(), arr, fas::range(jsonstring) );
  }
  catch(const aj::json_error& e)
  {
    std::string errmsg = e.message( fas::range(jsonstring) );
    
    user_error ue( sizeof(jsonstring) - e.tail_of(), errmsg );
    std::cout << std::endl << "[[" << ue.position << ":" <<  ue.description << "]]" << std::endl;

    typedef ajr::error_message_object< user_error> message_object;
    typedef ajr::error_message_json<  message_object, user_error, user_error_json > message_json;
    
    t.get_aspect().template get< ajr::_send_>()( t,
      message_json(),
      message_object( ue, 4 )
    );
  }

  jsonrpc = buffer(t);
  // {"jsonrpc":"2.0","error":{"code":-32700,"message":"Parse error.","data":{"position":5,"description":"parse error: [1,2,>>>},3,4,5]"}},"id":4}
  t << equal<expect>( jsonrpc, "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32700,\"message\":\"Parse error.\",\"data\":{\"position\":5,\"description\":\"parse error: [1,2,>>>},3,4,5]\"}},\"id\":4}" )
    << FAS_TESTING_FILE_LINE
    << std::endl << jsonrpc << std::endl;
  
}

BEGIN_SUITE(outgoing_error_suite, "outgoing aspect suite")
  ADD_UNIT(outgoing_error)
  ADD_UNIT(outgoing_custom_error)
  ADD_UNIT(outgoing_user_error)
  ADD_STUB( ajr::_output_ )
  ADD_VALUE_ADVICE( ajr::_buffer_, std::string )
  ADD_ASPECT( ajr::outgoing_aspect )
END_SUITE(outgoing_error_suite)
