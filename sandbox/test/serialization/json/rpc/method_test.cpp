#include <fas/serialization/json/rpc/method/aspect_type.hpp>
#include <iostream>

#include <fas/serialization/json/rpc/method/method_base.hpp>
#include <fas/serialization/json/rpc/method/name.hpp>
#include <fas/serialization/json/rpc/method/invoke_request.hpp>
#include <fas/serialization/json/rpc/method/request.hpp>
#include <fas/serialization/json/rpc/method/invoke_response.hpp>
#include <fas/serialization/json/rpc/method/value_json.hpp>



#include <fas/serialization/json/deser/deserializer.hpp>
#include <fas/serialization/json/ser/serializer.hpp>


#include <fas/typemanip/tstring.hpp>
#include <fas/aop/stub.hpp>
#include <fas/testing.hpp>



FAS_NAME(foo)

UNIT(name_test, "name method")
{
  using namespace fas;
  using namespace fas::testing;
  namespace ajrm = ::fas::json::rpc::method;
  
  ajrm::method_base<
    aspect<
      ajrm::name<n_foo>
    >
  > method;
  
  t << equal<expect>( method.name(), std::string("foo") ) << FAS_TESTING_FILE_LINE;
  
  t << is_true<expect>( method.check_name( make_string_range("foo") ) ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( method.check_name( make_string_range("foop") ) ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( method.check_name( make_string_range("foom") ) ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( method.check_name( make_string_range("foo ") ) ) << FAS_TESTING_FILE_LINE;
  t << is_false<expect>( method.check_name( make_string_range("fo") ) ) << FAS_TESTING_FILE_LINE;
}


struct foo_request
{
  template<typename T>
  bool operator()(T& t, int* req, int id, int& resp)
  {
    resp = req[0]+req[1];
    return true;
  }
};



UNIT(method_request_test, "method request")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json;
  namespace ajr = ::fas::json::rpc;
  namespace ajrm = ::fas::json::rpc::method;
  
  typedef ::fas::json::deser::deserializer<> deserializer_type;
  
  ajrm::method_base<
    aspect<
      typename type_list_n<
        ajrm::name<n_foo>,
        ajrm::request<foo_request>,
        ajrm::invoke_request< int[2] >,
        ajrm::invoke_request_json< array<integer> >,
        ajrm::invoke_response< int >,
        ajrm::invoke_response_json< integer >
      >::type
    >,
    ajrm::aspect_type
  > method;
  
  std::string req = "[10,20]";
  std::cout << "?????????" << std::endl;
  method.get_aspect().template get< ajr::_invoke_request_handler_>()(t, method, (req), 1);
  
  std::cout << std::string(
    t.get_aspect().template get< ajr::_outgoing_buffer_>().get_range().begin(),
    t.get_aspect().template get< ajr::_outgoing_buffer_>().get_range().end()
  ) << std::endl;
  
  /*
  
  std::string req="10";
  //method.get_aspect().template get< ajr::_invoke_method_>()(t, method, (req), 1);
  method.invoke_request(t, (req), 1);
  
  t << equal<expect>( method.name(), "foo" ) << FAS_TESTING_FILE_LINE;
  
  std::cout << "--------->" << method.get_aspect().template get< ajr::_invoke_response_>().value() << std::endl;
  //t << equal<expect>( resp, 10 ) << FAS_TESTING_FILE_LINE;
  */
}



BEGIN_SUITE(method_suite, "json-rpc method suite")
  ADD_UNIT(name_test)
  ADD_UNIT(method_request_test)
  ADD_STUB( ::fas::json::rpc::_outgoing_result_ )
  ADD_ADVICE( ::fas::json::rpc::_deserializer_, ::fas::json::deser::deserializer<> )
  ADD_ADVICE( ::fas::json::rpc::_serializer_, ::fas::json::ser::serializer<> )
  ADD_ADVICE( ::fas::json::rpc::_outgoing_buffer_, ::fas::json::rpc::method::ad_outgoing_buffer<> )
END_SUITE(method_suite)
