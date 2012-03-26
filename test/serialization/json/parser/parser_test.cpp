#include <fas/testing.hpp>

#include <fas/serialization/json/parser.hpp>
#include <fas/range.hpp>
#include <fstream>
#include <iostream>
#include <iterator>


UNIT(parser_test, "testing default parser")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json;

  parser<> jp;
  std::string s = "/*prev*/[ {\"jsonrpc\": \"2.0\", \"method\": \"sum\", \"params\": [1,2,4], \"id\": \"1\"},\
      {\"jsonrpc\": \"2.0\", \"method\": \"notify_hello\", \"params\": [7]},\
      {\"jsonrpc\": \"2.0\", \"method\": \"subtract\", \"params\": [42,23], \"id\": \"2\"},\
      {\"foo\": \"boo\"},\
      {\"jsonrpc\": \"2.0\", \"method\": \"foo.get\", \"params\": {\"name\": \"myself\"}, \"id\": \"5\"},\
      {\"jsonrpc\": \"2.0\", \"method\": \"get_data\", \"id\": \"9\"} ]/*next*/";

  std::string::iterator next = jp.parse( range(s.begin(), s.end() ) ).begin();
  t << equal<expect>("/*next*/", std::string(next, s.end()) );
}


BEGIN_SUITE(default_parser_suite, "default json parser suite")
  ADD_UNIT(parser_test)
END_SUITE(default_parser_suite)

