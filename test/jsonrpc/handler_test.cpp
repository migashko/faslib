
#include <fas/testing.hpp>
#include <fas/jsonrpc/handler/handler.hpp>

#include <fas/range.hpp>

#include <string>

namespace ajr = ::fas::jsonrpc;

UNIT(handler, "")
{
  using namespace ::fas::testing;
  std::string jsonrpc="{}";

  ajr::handler<> h;

  // h( fas::range( jsonrpc ) );
}

UNIT(handler_client, "")
{
}

UNIT(handler_server, "")
{
}

BEGIN_SUITE(handler_suite, "jsonrpc handler suite")
  ADD_UNIT(handler)
  ADD_UNIT(handler_client)
  ADD_UNIT(handler_server)
END_SUITE(handler_suite)
