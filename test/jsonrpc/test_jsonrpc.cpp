#include <fas/testing.hpp>

BEGIN_TEST
  RUN_SUITE(outgoing_suite)
  RUN_SUITE(outgoing_error_suite)
  RUN_SUITE(handler_suite)
  RUN_SUITE(common_suite)
  RUN_SUITE(method_suite)
  RUN_SUITE(error_suite)
  RUN_SUITE(invoke_suite)
  RUN_SUITE(call_suite)
END_TEST
