// #include <fas/system/disable_warnings.hpp>
#include <fas/testing.hpp>
#include <fas/jsonrpc/jsonrpc_handler.hpp>
#include <fas/jsonrpc/method.hpp>
#include <fas/jsonrpc/name.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/jsonrpc/notify.hpp>



/*
#pragma warning( push )
#pragma warning( disable: 4503 )
*/
// #include <fas/system/disable_warnings.hpp>
/*#ifdef _MSC_VER

#pragma warning( push )
#pragma warning( disable: 4503 )
#endif
*/



struct _update_;

struct update
{
  template<typename T>
  void operator()(T& t, const int params[3])
  {
    std::cout << "update_notify " << params[0] << params[1] << params[2] << params[3] << params[4] << std::endl;
  }

  template<typename T>
  void operator()(T& t, const int params[3], int id)
  {
    std::cout << "REQUEST update_notify " << params[0] << params[1] << params[2] << params[3] << params[4] << std::endl;
    t.get_aspect().template get<_update_>().response(t, params[0] + params[1] + params[2] + params[3] + params[4], id);
  }

  template<typename T>
  void operator()(T& t, ::fas::empty_type, int id)
  {
    
    t.get_aspect().template get<_update_>().response(t, ::fas::empty_type(), id);
  }

};

FAS_NAME(update);


struct update_notify_method
  : ::fas::jsonrpc::method<
      ::fas::aspect< ::fas::type_list_n<
        ::fas::jsonrpc::name<n_update>, 
        ::fas::jsonrpc::notify< update, int[5], fas::json::array< fas::json::integer > >,
        ::fas::jsonrpc::request< update >
      >::type > >
{
};

template<typename Tg, typename M>
struct advice_method
  : ::fas::type_list_n< 
      ::fas::advice< _update_, update_notify_method >, 
      ::fas::group< ::fas::jsonrpc::_method_, _update_ > 
    >::type 
{
};


struct jsonrpc_handler_aspect: 
  fas::aspect< 
    fas::type_list_n<
        advice_method< _update_, update_notify_method >
      >::type 
    >
{};

struct my_jsonrpc_handler
  : fas::jsonrpc::jsonrpc_handler< jsonrpc_handler_aspect >
{};

// #include <fas/system/disable_warnings.hpp>
UNIT(empty_handler, "")
{
  // #include <fas/system/enable_warnings.hpp>

  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json;
  using namespace fas::jsonrpc;
  

  
  my_jsonrpc_handler h;
  h( srange("{}") );

  t << equal<expect> ( h.result(), std::string("{}") ) << "[" << h.result() << "]" << FAS_TESTING_FILE_LINE;

  h.result().clear();
  h( srange("{\"jsonrpc\": \"2.0\", \"method\": \"update\", \"params\": [1,2,3,4,5]}") );
  t << equal<expect> ( h.result(), std::string("{}") ) << "[" << h.result() << "]" << FAS_TESTING_FILE_LINE;

  h.result().clear();
  h( srange("{\"jsonrpc\": \"2.0\", \"method\": \"update\", \"params\": [1,2,3,4,5], \"id\":1}") );
  t << equal<expect> ( h.result(), std::string("{}") ) << "[" << h.result() << "]" << FAS_TESTING_FILE_LINE;
}

BEGIN_SUITE(handler_suite, "jsonrpc_handler suite")
  ADD_UNIT(empty_handler)
END_SUITE(handler_suite)
