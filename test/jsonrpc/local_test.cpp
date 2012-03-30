#include <fas/testing.hpp>

#include <fas/jsonrpc/aspect.hpp>
#include <fas/jsonrpc/method.hpp>

#include <numeric>

namespace aj = ::fas::json;
namespace ajr = ::fas::jsonrpc;

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
inline std::string buffer(T& t)
{
  return t.get_aspect().template get< ajr::_output_ >().buffer;
}

template<typename T>
inline void clear(T& t)
{
  t.get_aspect().template get< ajr::_output_ >().buffer.clear();
}

/// /////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////

struct foo_notify
{
  int result;
  
  foo_notify(): result( 0 ) {}
  
  template<typename T, typename M>
  void operator()( T&, M&, const std::vector<int>& params)
  {
    result = std::accumulate( params.begin(), params.end(), 0 );
  }
};

struct foo_request
{
  int result;

  foo_request(): result( 0 ) {}

  template<typename T, typename M>
  void operator()( T&, M&, const std::vector<int>& params)
  {
    result = std::accumulate( params.begin(), params.end(), 0 );
  }
};

struct _foo_;

FAS_NAME(foo)

struct foo_method: ajr::method< fas::type_list_n<
  ajr::name< n_foo >,
  ajr::local::notify< foo_notify, std::vector<int>, aj::array< aj::integer > >,
  ajr::local::request< foo_request, std::vector<int>, aj::array< aj::integer > >,
  ajr::local::result< int, aj::integer >
>::type > {};

class jsonrpc: public fas::aspect_class< fas::type_list_n<
  fas::advice< ajr::_buffer_, std::string >,
  fas::advice< ajr::_output_, ad_output >,
  fas::advice< _foo_, foo_method>,
  ajr::aspect
>::type >
{
public:
  std::string operator()( const std::string& jsonrpc_string )
  {
    this->get_aspect().get< ajr::_output_ >().buffer.clear();
    this->get_aspect().get< ajr::_inbound_ >()( *this, fas::range( jsonrpc_string ) );
    return this->get_aspect().get< ajr::_output_ >().buffer;
  }
};



BEGIN_SUITE(local_suite, "json-rpc remote call suite")

END_SUITE(local_suite)
