
#include <fas/testing.hpp>

#include <fas/jsonrpc/handler/handler.hpp>
#include <fas/jsonrpc/method.hpp>

#include <fas/range.hpp>
#include <fas/typemanip/empty_type.hpp>

#include <string>

namespace ajr = ::fas::jsonrpc;
namespace aj = ::fas::json;

/**
 *  client --> notify(hi) --> server
 *  client <-- notify(hi) <-- server
 *  client <-- request(get_name) <-- server
 *  client --> result("client") --> server
 *  client --> request(get_name) --> server
 *  client <-- result("server") <-- server
 *  client --> request(hi) --> server
 *  client <-- error("Method not found") <-- server
 * 
*/
namespace {
struct _hi_;
struct _get_name_;

FAS_NAME(hi)
FAS_NAME(get_name)

namespace client
{
  struct context
  {
    bool hi_ready;
    std::string server_name;
    context(): hi_ready(false)
    {
      std::cout << "new client context" << std::endl;
    }
  };
  
  struct hi_notify
  {
    template<typename T, typename M>
    void operator()(T& t, M& m, fas::empty_type)
    {
      
      std::cout << "client: hi_notify" << std::endl;
      m.context().hi_ready = true;
    }
  };

  struct hi_error
  {
    template<typename T, typename M, typename E>
    void operator()(T&t, M& m, E& e, id_t id)
    {
      std::cout << "hi_error" << std::endl;
    }
  };

  

  struct get_name_request
  {
    template<typename T, typename M>
    void operator()(T&t, M& m, fas::empty_type, ajr::id_t id )
    {
      std::cout << "client: get_name_request " << m.context().hi_ready << std::endl;
      
      if ( t.get_aspect().template get<_hi_>().context().hi_ready )
      {
        std::cout << "client: get_name_request hi_ready" << std::endl;
        m.result(t, "client", id);
        m.request(t, fas::empty_type() );
      }
    }
  };

  struct get_name_result
  {
    template<typename T, typename M>
    void operator()(T&t, M& m, const std::string& name, ajr::id_t id )
    {
      std::cout << "client: get_name_result " << name << std::endl;
      m.context().server_name = name;
      t.get_aspect().template get< _hi_>().request(t, fas::empty_type() );
    }
  };

  /*struct hi_method_aspect:*/ typedef fas::aspect< fas::type_list_n<
    ajr::name<n_hi>,
    ajr::local::notify< hi_notify >,
    ajr::remote::notify<>,
    ajr::remote::request<>,
    ajr::remote::error< hi_error >,
    fas::value_advice< ajr::_context_, context >
  >::type > /*{}*/ hi_method_aspect;

  /*struct get_name_method_aspect:*/  typedef fas::aspect< fas::type_list_n<
    ajr::name<n_get_name>,
    ajr::local::request< get_name_request >,
    ajr::local::result< std::string, aj::string >,
    ajr::remote::request<  >,
    ajr::remote::result< get_name_result, std::string, aj::string >,
    fas::value_advice< ajr::_context_, context >
  >::type > /*{}*/  get_name_method_aspect;

  
  typedef ajr::method< hi_method_aspect > hi_method;
  typedef ajr::method< get_name_method_aspect > get_name_method;

  /*
  struct hi_method
    : ajr::method< hi_method_aspect >
  {
  };

  struct get_name_method
    : ajr::method< get_name_method_aspect >
  {
  };
  */
}


/*struct client_method_aspect:*/ typedef fas::aspect< fas::type_list_n<
  fas::advice<_hi_, client::hi_method>,
  fas::advice<_get_name_, client::get_name_method>,
  fas::group< ajr::_notify_group_ ,  _hi_  >,
  fas::group< ajr::_request_group_,  _get_name_ >,
  fas::group< ajr::_result_group_ ,  _get_name_ >,
  fas::group< ajr::_error_group_ ,  _hi_ >
>::type > client_method_aspect /*{}*/;


namespace server
{
  struct context
  {
    bool hi_ready;
    std::string client_name;
    context(): hi_ready(false){}
  };

  struct hi_notify
  {
    template<typename T, typename M>
    void operator()(T&t, M& m, fas::empty_type)
    {
      m.context().hi_ready = true;
      m.notify(t, fas::empty_type() );
      t.get_aspect().template get< _get_name_ >().request(t, fas::empty_type() );
    }
  };


  struct get_name_result
  {
    template<typename T, typename M>
    void operator()(T&t, M& m, const std::string& name, ajr::id_t id )
    {
      m.context().client_name = name;
    }
  };

  struct get_name_request
  {
    template<typename T, typename M>
    void operator()(T&t, M& m, fas::empty_type, ajr::id_t id )
    {
      m.result(t, "server", id);
    }
  };


  
  /*struct hi_method_aspect:*/ typedef fas::aspect< fas::type_list_n<
    ajr::name<n_hi>,
    ajr::local::notify< hi_notify >,
    ajr::remote::notify<>,
    fas::value_advice< ajr::_context_, context >
  >::type > hi_method_aspect /*{}*/;

  /*struct get_name_method_aspect:*/ typedef fas::aspect< fas::type_list_n<
    ajr::name<n_get_name>,
    ajr::local::request< get_name_request >,
    ajr::local::result< std::string, aj::string >,
    ajr::remote::request< >,
    ajr::remote::result< get_name_result, std::string, aj::string >,
    fas::value_advice< ajr::_context_, context >
  >::type > /*{}*/ get_name_method_aspect;

  
  
  typedef ajr::method< hi_method_aspect > hi_method;
  typedef ajr::method< get_name_method_aspect > get_name_method;
  /*
  struct hi_method
    : ajr::method< hi_method_aspect >
  {
  };

  struct get_name_method
    : ajr::method< get_name_method_aspect >
  {
  };
  */

  
}


typedef fas::aspect< fas::type_list_n<
  fas::advice<_hi_, server::hi_method>,
  fas::advice<_get_name_, server::get_name_method>,
  fas::group< ajr::_notify_group_ ,  _hi_  >,
  fas::group< ajr::_request_group_,  _get_name_ >,
  fas::group< ajr::_result_group_ ,  _get_name_ >
>::type > server_method_aspect;

/*
struct server_method_aspect: fas::aspect< fas::type_list_n<
  fas::advice<_hi_, server::hi_method>,
  fas::advice<_get_name_, server::get_name_method>,
  fas::group< ajr::_notify_group_ ,  _hi_  >,
  fas::group< ajr::_request_group_,  _get_name_ >,
  fas::group< ajr::_result_group_ ,  _get_name_ >
>::type > {};
*/


/*
{"jsonrpc":"2.0","method":"hi","params":null}
{"jsonrpc":"2.0","method":"hi","params":null}{"jsonrpc":"2.0","method":"get_name","params":null,"id":1}
{"jsonrpc":"2.0","result":"client","id":1}{"jsonrpc":"2.0","method":"get_name","params":null,"id":1}
{"jsonrpc":"2.0","result":"server","id":1}
{"jsonrpc":"2.0","method":"hi","params":null,"id":1}
{"jsonrpc":"2.0","error":{"code":-32601,"message":"Method not found."},"id":1}
*/


/*
struct handler_client: ajr::handler<client_method_aspect>{};
struct handler_server: ajr::handler<server_method_aspect>{};
*/

typedef ajr::handler<client_method_aspect> handler_client;
typedef ajr::handler<server_method_aspect> handler_server;

  handler_client hclient;
  handler_server hserver;

  //832532
}

UNIT(handler_unit, "")
{
  using namespace ::fas::testing;


  std::string result;
  std::string check_result;
  std::string current;

  current = hclient.notify<_hi_>( fas::empty_type() );
  result+=current;
  t << equal<expect>( current, "{\"jsonrpc\":\"2.0\",\"method\":\"hi\",\"params\":null}" )
    << FAS_TESTING_FILE_LINE << std::endl << current;
  
  
  current = hserver.parse( fas::range(current) );
  result+=current;
  t << equal<expect>( current, "{\"jsonrpc\":\"2.0\",\"method\":\"hi\",\"params\":null}{\"jsonrpc\":\"2.0\",\"method\":\"get_name\",\"params\":null,\"id\":1}")
    << FAS_TESTING_FILE_LINE << std::endl << current;

  current = hclient.parse( fas::range(current) );
  result+=current;
  t << equal<expect>( current, "{\"jsonrpc\":\"2.0\",\"result\":\"client\",\"id\":1}{\"jsonrpc\":\"2.0\",\"method\":\"get_name\",\"params\":null,\"id\":1}")
    << FAS_TESTING_FILE_LINE << std::endl << current;
  
  current = hserver.parse( fas::range(current) );
  result+=current;
  t << equal<expect>( current, "{\"jsonrpc\":\"2.0\",\"result\":\"server\",\"id\":1}")
    << FAS_TESTING_FILE_LINE << std::endl << current;

  current = hclient.parse( fas::range(current) );
  result+=current;
  t << equal<expect>( current, "{\"jsonrpc\":\"2.0\",\"method\":\"hi\",\"params\":null,\"id\":1}")
    << FAS_TESTING_FILE_LINE << std::endl << current;

  current = hserver.parse( fas::range(current) );
  result+=current;
  
  t << equal<expect, std::string>(current, "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32601,\"message\":\"Method not found.\"},\"id\":1}")
    << FAS_TESTING_FILE_LINE
    << std::endl << current
    ;

  std::cout << std::endl << current << std::endl;
  current = hclient.parse( fas::range(current) );

  
  
  
/*  using namespace ::fas::testing;
  std::string jsonrpc="{}";

  ajr::handler<> h;

  h( fas::range( jsonrpc ) );
  
  std::cout << std::endl << "[" << h.result() << "]"<< std::endl;
  */
}

UNIT(handler_client_unit, "")
{
}

UNIT(handler_server_unit, "")
{
}

BEGIN_SUITE(handler_suite, "jsonrpc handler suite")
  ADD_UNIT(handler_unit)
  ADD_UNIT(handler_client_unit)
  ADD_UNIT(handler_server_unit)
END_SUITE(handler_suite)
