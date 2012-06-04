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

  std::string::iterator next;
  typerange<std::string>::range sr = range(s);
  try{
  next = jp.parse( sr ).begin();
  t << equal<expect>("/*next*/", std::string(next, s.end()) );
  }
  catch(const json_error& e)
  {
    t << fail( e.message(sr) );
  }
}

UNIT(copy_parse_unit, "")
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
  std::string test = "[{\"jsonrpc\":\"2.0\",\"method\":\"sum\",\"params\":[1,2,4],\"id\":\"1\"},"
      "{\"jsonrpc\":\"2.0\",\"method\":\"notify_hello\",\"params\":[7]},"
      "{\"jsonrpc\":\"2.0\",\"method\":\"subtract\",\"params\":[42,23],\"id\":\"2\"},"
      "{\"foo\":\"boo\"},"
      "{\"jsonrpc\":\"2.0\",\"method\":\"foo.get\",\"params\":{\"name\":\"myself\"},\"id\":\"5\"},"
      "{\"jsonrpc\":\"2.0\",\"method\":\"get_data\",\"id\":\"9\"}]";

  std::string result;
  std::string::iterator next = jp.copy( range(s), orange(result) ).first.begin();
  t << equal<expect>("/*next*/", std::string(next, s.end()) ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result, test) << FAS_TESTING_FILE_LINE 
    << std::endl << test;
}


BEGIN_SUITE(default_parser_suite, "")
  ADD_UNIT(parser_test)
  ADD_UNIT(copy_parse_unit)
END_SUITE(default_parser_suite)

