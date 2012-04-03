#include <fas/testing.hpp>

#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/sequence.hpp>
#include <fas/serialization/json/ser/ad_integer.hpp>
#include <fas/serialization/json/except/ad_except.hpp>

#include <fas/serialization/json/ser/ad_sequence.hpp>
#include <fas/serialization/json/ser/serialize_sequence.hpp>
#include <fas/serialization/json/ser/serialize_integer.hpp>
#include <fas/range/range.hpp>
#include <fas/typemanip/tstring.hpp>

#include <vector>
#include <string>

struct f_int
{
  template<typename R>
  R operator()( int value, R r)
  {
    using namespace ::fas::json;
    return serialize_integer( value, r);
  }
};

UNIT(sequence_serialize_test, "test sequence_serialize function")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  std::string result;
  std::vector<int> value;
  serialize_sequence( range(value), init_range(result), f_int() );
  t << equal<expect>(result, "") << FAS_TESTING_FILE_LINE;

  result.clear();
  value.push_back(0);
  serialize_sequence( range(value), init_range(result), f_int() );
  t << equal<expect>(result, "0") << FAS_TESTING_FILE_LINE;

  result.clear();
  value.push_back(-1);
  serialize_sequence( range(value), init_range(result), f_int() );
  t << equal<expect>(result, "0,-1") << FAS_TESTING_FILE_LINE;

  result.clear();
  value.push_back(1000);
  serialize_sequence( range(value), init_range(result), serialize_integer<int, typerange<std::string>::init_range> );
  t << equal<expect>(result, "0,-1,1000") << FAS_TESTING_FILE_LINE;
}

UNIT(ad_sequence_test, "test ad_sequence advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  std::string result;
  std::vector<int> value;

  ad_sequence ads;
  t << is_false<expect>( ads.check(t, sequence<integer>(), value) ) << FAS_TESTING_FILE_LINE;
  ads(t, sequence<integer>(), value, init_range(result));
  t << equal<expect>(result, "") << FAS_TESTING_FILE_LINE;

  result.clear();
  value.push_back(0);
  t << is_true<expect>( ads.check(t, sequence<integer>(), value) ) << FAS_TESTING_FILE_LINE;
  ads(t, sequence<integer>(), value, init_range(result));
  t << equal<expect>(result, "0") << FAS_TESTING_FILE_LINE;

  result.clear();
  value.push_back(-1);
  t << is_true<expect>( ads.check(t, sequence<integer>(), value) ) << FAS_TESTING_FILE_LINE;
  ads(t, sequence<integer>(), value, init_range(result));
  t << equal<expect>(result, "0,-1") << FAS_TESTING_FILE_LINE;

  result.clear();
  value.push_back(1000);
  t << is_true<expect>( ads.check(t, sequence<integer>(), value) ) << FAS_TESTING_FILE_LINE;
  ads(t, sequence<integer>(), value, init_range(result));
  t << equal<expect>(result, "0,-1,1000") << FAS_TESTING_FILE_LINE;
}

UNIT(ad_sequence_test2, "test ad_sequence advice 2")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::ser;

  std::string result;
  int value[3] = {0, -1, 1000};

  ad_sequence ads;
  t << is_false<expect>( ads.check(t, sequence<integer, 0>(), value) ) << FAS_TESTING_FILE_LINE;
  ads(t, sequence<integer, 0>(), value, init_range(result));
  t << equal<expect>(result, "") << FAS_TESTING_FILE_LINE << std::endl << result;

  result.clear();
  //value.push_back(0);
  t << is_true<expect>( ads.check(t, sequence<integer, 1>(), value) ) << FAS_TESTING_FILE_LINE;
  ads(t, sequence<integer, 1>(), value, init_range(result));
  t << equal<expect>(result, "0") << FAS_TESTING_FILE_LINE;

  result.clear();
  //value.push_back(-1);
  t << is_true<expect>( ads.check(t, sequence<integer, 2>(), value) ) << FAS_TESTING_FILE_LINE;
  ads(t, sequence<integer, 2>(), value, init_range(result));
  t << equal<expect>(result, "0,-1") << FAS_TESTING_FILE_LINE;

  result.clear();
  //value.push_back(1000);
  t << is_true<expect>( ads.check(t, sequence<integer, 3>(), value) ) << FAS_TESTING_FILE_LINE;
  ads(t, sequence<integer, 3>(), value, init_range(result));
  t << equal<expect>(result, "0,-1,1000") << FAS_TESTING_FILE_LINE;
}


BEGIN_SUITE(sequence_serializer_suite, "sequence serializer suite")
  ADD_UNIT(sequence_serialize_test)
  ADD_UNIT(ad_sequence_test)
  ADD_UNIT(ad_sequence_test2)
  ADD_ADVICE( ::fas::json::ser::_integer_, ::fas::json::ser::ad_integer)
  ADD_ADVICE( ::fas::json::_except_, ::fas::json::ad_except)
END_SUITE(sequence_serializer_suite)
