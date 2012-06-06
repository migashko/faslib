#include <fas/testing.hpp>


UNIT(ad_ids_test, "ad_ids")
{
}

BEGIN_SUITE(common_suite, "json-rpc common suite")
  ADD_UNIT(ad_ids_test)
END_SUITE(common_suite)
