#include <fas/testing.hpp>
#include <fas/typemanip/tstring.hpp>

#include <fas/serialization/json/meta.hpp>
#include <fas/jsonrpc/method/method.hpp>
#include <fas/jsonrpc/method/name.hpp>
#include <fas/jsonrpc/method/request.hpp>
#include <fas/jsonrpc/method/result.hpp>
#include <fas/jsonrpc/method/remote_notify.hpp>
#include <fas/jsonrpc/method/remote_request.hpp>
#include <fas/jsonrpc/method/remote_result.hpp>
#include <fas/jsonrpc/method/notify.hpp>

#include <fas/jsonrpc/outgoing/outgoing_aspect.hpp>
#include <fas/jsonrpc/json/json_aspect.hpp>
#include <fas/jsonrpc/error/error_aspect.hpp>
#include <fas/jsonrpc/invoke/invoke_aspect.hpp>
#include <fas/range.hpp>

namespace ajr = ::fas::jsonrpc;
namespace aj = ::fas::json;

struct method_request
{
  typedef int params_type[2];
  
  template<typename T, typename M>
  void operator()( T&t, M& m, const int params[2], int id)
  {
    m.result( t, m, params[0] + params[1], id );
  }
};

struct method_notify
{
  typedef int params_type[2];
  
  template<typename T, typename M>
  void operator()( T&t, M& m, const int params[2] )
  {
    m.request( t, m, params[0] + params[1] );
  }
};


FAS_NAME(method)

typedef ajr::method<
  fas::type_list_n<
    ajr::name<n_method>,
    ajr::request< method_request, method_request::params_type, aj::array<aj::integer> >,
    ajr::result<int, aj::integer>,
    ajr::notify< method_notify, method_notify::params_type, aj::array<aj::integer> >,
    ajr::remote_notify< int, aj::integer>,
    ajr::remote_request< int, aj::integer>,
    ajr::remote_result< method_request, method_request::params_type, aj::array<aj::integer> >
  >::type
> method_test_request;


UNIT(request, "")
{
  std::string jsonstring = "[1,2]";
  method_test_request mtr;
  mtr.get_aspect().get<ajr::_parse_request_>()(t, mtr, fas::range(jsonstring), 1 ); 
  std::cout << "[" << t.get_aspect().template get< ajr::_buffer_>() << "]" << std::endl;
  t.get_aspect().template get< ajr::_buffer_>().clear();
  mtr.get_aspect().get<ajr::_parse_notify_>()(t, mtr, fas::range(jsonstring) );
  std::cout << "[" << t.get_aspect().template get< ajr::_buffer_>() << "]" << std::endl;
  mtr.get_aspect().get<ajr::_parse_response_>()(t, mtr, fas::range(jsonstring), 1 );
  std::cout << "[" << t.get_aspect().template get< ajr::_buffer_>() << "]" << std::endl;
}

BEGIN_SUITE(method_suite, "json-rpc method suite")
  ADD_UNIT(request)
  ADD_VALUE_ADVICE( ajr::_buffer_, std::string )
  ADD_ASPECT( ajr::invoke_aspect )
  ADD_ASPECT( ajr::outgoing_aspect )
  ADD_ASPECT( ajr::json_aspect )
  ADD_ASPECT( ajr::error_aspect )
  ADD_STUB( ajr::_output_ )
END_SUITE(method_suite)
