#include <fas/testing.hpp>
/*
#include <fas/serialization/json/rpc/aspect.hpp>
#include <fas/serialization/json/rpc/method/name.hpp>
#include <fas/serialization/json/rpc/method/aspect_type.hpp>
#include <fas/serialization/json/rpc/method/method_base.hpp>

#include <fas/range/.hpp>

#include <fas/serialization/json/rpc/json_rpc.hpp>

struct _foo_;
struct _bar_;

struct foo_request
{
  template<typename T>
  bool operator()(T& t, int req[2], int id, int& resp)
  {
    resp = req[0]+req[1];
    return true;
  }
};

struct bar_request
{
  template<typename T>
  bool operator()(T& t, int req[2], int id, int& resp)
  {
    std::cout << "sizeof: " <<  sizeof(req) << std::endl;
    resp = req[0]*req[1];
    return true;
  }
};

namespace ajrm = ::fas::json::rpc::method;

FAS_NAME(foo)
FAS_NAME(bar)

typedef ::fas::type_list_n<
  ajrm::invoke_request< int[2] >,
  ajrm::invoke_request_json< ::fas::json::array< ::fas::json::integer > >,
  ajrm::invoke_response< int >,
  ajrm::invoke_response_json< ::fas::json::integer >
>::type foo_list;

typedef ajrm::method_base< 
  ::fas::aspect< 
    ::fas::type_list_n<
      ajrm::name<n_foo>,
      ajrm::request<foo_request>,
      foo_list
    >::type 
  >,
  ajrm::aspect_type
> foo_method;

typedef ajrm::method_base< 
  ::fas::aspect< 
    ::fas::type_list_n<
      ajrm::name<n_bar>,
      ajrm::request<bar_request>,
      foo_list
    >::type 
  >,
  ajrm::aspect_type
> bar_method;


UNIT(ad_invoke_test, "ad_invoke ")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::rpc;
  
  //! except std::string req="{\"jsonrpc\":\"2.0\", \"method\":\"bar\", \"params\": [ 1, 2, 3 ], \"id\":1 }";
  std::string req="{\"jsonrpc\":\"2.0\", \"method\":\"bar\", \"params\": [ 2, 3 ], \"id\":1 }";
  
  t.get_aspect().template get<_invoke_>()( t, (req) );
  
  req="{\"jsonrpc\":\"2.0\", \"method\":\"foo\", \"params\": [ 2, 3 ], \"id\":1 }";
  t.get_aspect().template get<_invoke_>()( t, (req) );

  std::cout << "-------------------<" << std::endl;
  std::cout << std::string(
    t.get_aspect().template get< _outgoing_buffer_>().get_range().begin(),
    t.get_aspect().template get< _outgoing_buffer_>().get_range().end()
  ) << std::endl;
  std::cout << ">->------------------" << std::endl;

}

UNIT(json_rpc_test, "json_rpc")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::rpc;
  
  json_rpc_base<typename T::aspect_type> jr;
  std::string req="{\"jsonrpc\":\"2.0\", \"method\":\"bar\", \"params\": [ 2, 3 ], \"id\":1 }"
                  "{\"jsonrpc\":\"2.0\", \"method\":\"foo\", \"params\": [ 2, 3 ], \"id\":2 }"
                  "{\"jsonrpc\":\"2.0\", \"method\":\"bar\", \"params\": [ 2, 3 ], \"id\":1 }"
                  "{\"jsonrpc\":\"2.0\", \"method\":\"foo\", \"params\": [ 2, 3 ], \"id\":1 }";
  
  jr(t, (req) );
  //std::cout << std::string( jr.buffer(t).begin(), jr.buffer(t).end() ) << std::endl;
  
  
}


typedef ::fas::type_list_n<_foo_,_bar_>::type method_group;
*/
BEGIN_SUITE(invoke_suite, "json-rpc invoke suite")
/*
  ADD_UNIT(ad_invoke_test)
  ADD_UNIT(json_rpc_test)
  ADD_ADVICE( _foo_, foo_method )
  ADD_ADVICE( _bar_, bar_method )
  ADD_ASPECT( ::fas::json::rpc::aspect )
  ADD_GROUP( ::fas::json::rpc::_method_,  method_group )
  */
END_SUITE(invoke_suite)
