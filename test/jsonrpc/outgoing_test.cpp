#include <fas/jsonrpc/outgoing/outgoing_aspect.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/testing.hpp>
#include <fas/range.hpp>

namespace aj = ::fas::json;
namespace ajr = ::fas::jsonrpc;

typedef char buffer_type[10];

struct ad_send_fail
{
  int count;

  ad_send_fail(): count(0) {};

  template<typename T, typename J, typename V, typename R>
  void operator() ( T&, J, const V&, R r, const aj::json_error& e )
  {
    // std::cout << e.message(r) << std::endl;
    ++count;
  }
};


struct ad_output
{
  std::string buffer;
  template<typename T, typename R>
  void operator()(T& t, R r)
  {
    if ( !r ) --r;
    if ( r ) *r = '\0';
    buffer += t.get_aspect().template get< ajr::_buffer_ >();
    //std::cout << t.get_aspect().template get< ajr::_buffer_ >() << std::endl;
  }
};

template<typename T>
inline std::string buffer(T& t)
{
  return t.get_aspect().template get< ajr::_output_ >().buffer;
}

template<typename T>
inline void clear(T& t)
{
  t.get_aspect().template get< ajr::_output_ >().buffer.clear();
}

template<typename T>
int fail_count(T& t) { return t.get_aspect().template get< ajr::_send_failed_>().count; }

UNIT(outgoing, "")
{
  using namespace ::fas::testing;
  
  // char *buffer = t.get_aspect().template get< ajr::_buffer_ >();

  bool send_result = false;
  send_result = t.get_aspect().template get< ajr::_send_ >()( t, aj::integer(), 10 );

  t << is_true<expect>( send_result ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( 0, fail_count(t) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect, std::string>( buffer(t), "10" ) << FAS_TESTING_FILE_LINE
    << std::endl << buffer(t) << std::endl;
  clear(t);

  int arr[10]={0};

  /*
  aj::serializer<> ser;
  std::string tmp;
  ser( aj::array< aj::sequence< aj::integer, 4> >(), arr, fas::orange(tmp) );
  std::cout << tmp << std::endl;*/

  send_result = t.get_aspect().template get< ajr::_send_ >()( t, aj::array< aj::sequence< aj::integer, 4> >(), arr );
  t << is_true<expect>( send_result ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( 0, fail_count(t) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect, std::string>( buffer(t), "[0,0,0,0]" ) << FAS_TESTING_FILE_LINE
    << std::endl << buffer(t) << std::endl;
  clear(t);
  
  send_result = t.get_aspect().template get< ajr::_send_ >()( t, aj::array< aj::integer >(), arr );
  t << is_false<expect>( send_result ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( 1, fail_count(t) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect, std::string>( buffer(t), "" ) << FAS_TESTING_FILE_LINE
    << std::endl << buffer(t) << std::endl;
  clear(t);

  std::string test="test";
  send_result = t.get_aspect().template get< ajr::_send_ >()( t, aj::string(), test );
  t << is_true<expect>( send_result ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>( 1, fail_count(t) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect, std::string>( buffer(t), "\"test\"" ) << FAS_TESTING_FILE_LINE
    << std::endl << buffer(t) << std::endl;
  clear(t);
}


BEGIN_SUITE(outgoing_suite, "outgoing aspect suite")
  ADD_UNIT(outgoing)
  ADD_ADVICE( ajr::_send_failed_, ad_send_fail )
  ADD_VALUE_ADVICE( ajr::_buffer_, buffer_type )
  ADD_ADVICE( ajr::_output_, ad_output )
  ADD_ASPECT( ajr::outgoing_aspect )
END_SUITE(outgoing_suite)
