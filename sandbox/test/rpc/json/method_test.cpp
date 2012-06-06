#include <fas/testing.hpp>
#include <fas/typemanip/tstring.hpp>
#include <fas/range/.hpp>


#include <fas/rpc/json/test/method.hpp>

#include <fas/serialization/json/meta/array.hpp>
#include <fas/serialization/json/meta/integer.hpp>

FAS_NAME(foo)
FAS_NAME(bar)

struct foo
{
  int result;
  template<typename T>
  void operator()(T& t, void*)
  {
    
  }

  template<typename T>
  void operator()(T& t, void* req, int id)
  {
    
  }
};


struct bar
{
  int result;
  bar(): result(0) {}
  template<typename T>
  void operator()(T& t, int* req)
  {
    result = req[0]+req[1];
  }

  template<typename T>
  void operator()(T& t, int* req, int id)
  {
    result = req[0]+req[1];
  }
};


UNIT(name_test, "name method")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::rpc::json;
  
  test::method< aspect< ::fas::rpc::json::name<n_foo> > > m;
  
  // test::method< foo_method::aspect_type > method;

  t << equal<expect>( m.name(), std::string("foo") ) << FAS_TESTING_FILE_LINE;
  t << is_true<expect>( m.check_name( make_string_range("foo") ) ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( m.check_name( make_string_range("foop") ) ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( m.check_name( make_string_range("foom") ) ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( m.check_name( make_string_range("foo ") ) ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( m.check_name( make_string_range("fo") ) ) << FAS_TESTING_FILE_LINE;
  
  m.result().clear();
}

UNIT(invoke_notimpl_test, "invoke not impl")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::rpc::json;
  
  const char* method_not_found = "{\"code\":-32601,\"message\":\"Method not found.\"}";
  const char* invalid_request = "{\"code\":-32600,\"message\":\"Invalid Request.\"}";
  
  test::method< aspect< ::fas::rpc::json::name<n_foo> > > method;
  method.invoke_request( make_string_range("1"), 1 );
  t << equal<expect>( method.result(), method_not_found ) << "[" << method.result() << "]" << FAS_TESTING_FILE_LINE;
  method.result().clear();
  
  method.invoke_notify( make_string_range("1"));
  t << equal<expect>( method.result(), method_not_found ) << "[" << method.result() << "]" << FAS_TESTING_FILE_LINE;
  method.result().clear();
  
  method.invoke_result( make_string_range("1"), 1 );
  t << equal<expect>( method.result(), invalid_request ) << "[" << method.result() << "]" << FAS_TESTING_FILE_LINE;
  method.result().clear();
  
  method.invoke_error( make_string_range("1"), 1 );
  t << equal<expect>( method.result(), invalid_request ) << "[" << method.result() << "]" << FAS_TESTING_FILE_LINE;
  method.result().clear();
  
  method.invoke_error( make_string_range("1") );
  t << equal<expect>( method.result(), invalid_request ) << "[" << method.result() << "]" << FAS_TESTING_FILE_LINE;
  method.result().clear();
}

UNIT(notify_test, "notify")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::rpc::json;
  using namespace ::fas::json;
  
  
  test::method< aspect< type_list_n<
    ::fas::rpc::json::name<n_foo>,
    ::fas::rpc::json::notify<foo>
  >::type > > method1;

  const char* method_not_found = "{\"code\":-32601,\"message\":\"Method not found.\"}";
  const char* invalid_request = "{\"code\":-32600,\"message\":\"Invalid Request.\"}";
  const char* parse_error = "{\"code\":-32600,\"message\":\"Invalid Request.\"}";
  
  int params[2]={1, 2};
  method1.get_aspect().get<_notify_>()(method1, 0);
  method1.invoke_notify( make_string_range("bla-bla"));
  t << equal<expect>( method1.result(), method_not_found ) << "[" << method1.result() << "]" << FAS_TESTING_FILE_LINE;
  method1.result().clear();

  test::method< aspect< type_list_n<
    ::fas::rpc::json::name<n_bar>,
    notify<bar>,
    notify_type<int[2]>,
    notify_json< array<integer> > 
  >::type > > method2;

  method2.get_aspect().get<_notify_>()(method2, params);
  method2.invoke_notify( make_string_range("bla-bla"));
  t << equal<expect>( method2.result(), invalid_request ) << "[" << method2.result() << "]" << FAS_TESTING_FILE_LINE;
  method2.result().clear();

  method2.invoke_notify( make_string_range("1"));
  t << equal<expect>( method2.result(), invalid_request ) << "[" << method2.result() << "]" << FAS_TESTING_FILE_LINE;
  method2.result().clear();

  method2.invoke_notify( make_string_range("1,2"));
  t << equal<expect>( method2.result(), invalid_request ) << "[" << method2.result() << "]" << FAS_TESTING_FILE_LINE;
  method2.result().clear();

  method2.invoke_notify( make_string_range("{1,2}"));
  t << equal<expect>( method2.result(), invalid_request ) << "[" << method2.result() << "]" << FAS_TESTING_FILE_LINE;
  method2.result().clear();

  method2.invoke_notify( make_string_range("[1,2]"));
  t << equal<expect>( method2.result(), "" ) << "[" << method2.result() << "]" << FAS_TESTING_FILE_LINE;
  t << equal<expect>( method2.get_aspect().get<_notify_>().result, 3 ) << FAS_TESTING_FILE_LINE;
  method2.result().clear();

}



BEGIN_SUITE(method_suite, "json-rpc method suite")
  ADD_UNIT(name_test)
  ADD_UNIT(invoke_notimpl_test)
  ADD_UNIT(notify_test)
/*  ADD_UNIT(method_request_test)
  ADD_STUB( ::fas::json::rpc::_outgoing_result_ )
  ADD_ADVICE( ::fas::json::rpc::_deserializer_, ::fas::json::deser::deserializer<> )
  ADD_ADVICE( ::fas::json::rpc::_serializer_, ::fas::json::ser::serializer<> )
  ADD_ADVICE( ::fas::json::rpc::_outgoing_buffer_, ::fas::json::rpc::method::ad_outgoing_buffer<> )
  */
END_SUITE(method_suite)
