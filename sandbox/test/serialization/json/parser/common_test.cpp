#include <fas/testing.hpp>

#include <fas/serialization/json/parser/ad_space.hpp>
#include <fas/serialization/json/parser/ad_null.hpp>
#include <fas/serialization/json/parser/ad_boolean.hpp>
#include <fas/serialization/json/parser/ad_number.hpp>
#include <fas/serialization/json/parser/ad_string.hpp>
#include <fas/serialization/json/parser/ad_simple_string.hpp>

#include <fas/serialization/json/except/ad_except.hpp>
#include <fas/serialization/json/except/tags.hpp>
#include <fas/range.hpp>
#include <fstream>
#include <iostream>
#include <iterator>


UNIT(space_test, "parse space")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;
  ad_space ads;
  std::string s = "";
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );
  t << is_true<assert>(!r) << FAS_TESTING_FILE_LINE;
  r = ads(t, r);
  t << is_true<assert>(!r) << FAS_TESTING_FILE_LINE ;

  s = "10";
  r = range_type( s.begin(), s.end() );
  r = ads(t, r);
  t << equal<assert>( s, std::string(r.begin(), r.end()) ) << s  << FAS_TESTING_FILE_LINE;
  t << stop;
  s = "\t 10";
  r = range_type( s.begin(), s.end() );
  r = ads(t, r);
  t << equal<assert>( std::string("10"), std::string(r.begin(), r.end()) ) << s  << FAS_TESTING_FILE_LINE;
  std::cout << "[" << std::string(r.begin(), r.end()) << "]" << std::endl;
  t << stop;

  s = "/**/ 10";
  r = range_type( s.begin(), s.end() );
  r = ads(t, r);
  t << equal<assert>( "10", std::string(r.begin(), r.end()) ) << s  << FAS_TESTING_FILE_LINE;
  t << stop;
  
  s = "\t /**/ 10";
  r = range_type( s.begin(), s.end() );
  r = ads(t, r);
  t << equal<assert>( "10", std::string(r.begin(), r.end()) ) << s  << FAS_TESTING_FILE_LINE;

  s = "/* \t aaa */ 10";
  r = range_type( s.begin(), s.end() );
  r = ads(t, r);
  t << equal<assert>( "10", std::string(r.begin(), r.end()) ) << s << FAS_TESTING_FILE_LINE;
  t << stop;
  
  s = "\t/* \t aaa */ /*<*/ 10";
  r = range_type( s.begin(), s.end() );
  r = ads(t, r);
  t << equal<assert>( "10", std::string(r.begin(), r.end()) ) << s << FAS_TESTING_FILE_LINE;
  t << stop;
}

UNIT(copy_space_test, "copy parse space")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;
  
  std::string dst;
  ad_space ads;
  std::string s = "";
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );
  t << is_true<assert>(!r) << FAS_TESTING_FILE_LINE;
  /*r = */ads(t, r, orange(dst) );
  t << is_true<assert>( dst.empty() ) << FAS_TESTING_FILE_LINE;

  s = "10";
  dst.clear();
  r = range_type( s.begin(), s.end() );
  r = ads(t, r, orange(dst)).first;
  t << is_true<assert>( dst.empty() ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( s, std::string(r.begin(), r.end()) ) << s  << FAS_TESTING_FILE_LINE;

  s = "\t 10";
  dst.clear();
  r = range_type( s.begin(), s.end() );
  r = ads(t, r, orange(dst)).first;
  t << is_true<assert>( dst.empty() ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "10", std::string(r.begin(), r.end()) ) << s  << FAS_TESTING_FILE_LINE;

  s = "/**/ 10";
  dst.clear();
  r = range_type( s.begin(), s.end() );
  r = ads(t, r, orange(dst)).first;
  t << is_true<assert>( dst.empty() ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "10", std::string(r.begin(), r.end()) ) << s  << FAS_TESTING_FILE_LINE;

  s = "\t /**/ 10";
  dst.clear();
  r = range_type( s.begin(), s.end() );
  r = ads(t, r, orange(dst)).first;
  t << is_true<assert>( dst.empty() ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "10", std::string(r.begin(), r.end()) ) << s  << FAS_TESTING_FILE_LINE;
  
  s = "/* \t aaa */ 10";
  dst.clear();
  r = range_type( s.begin(), s.end() );
  r = ads(t, r, orange(dst)).first;
  t << is_true<assert>( dst.empty() ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "10", std::string(r.begin(), r.end()) ) << s << FAS_TESTING_FILE_LINE;

  s = "\t/* \t aaa */ /*<*/ 10";
  dst.clear();
  r = range_type( s.begin(), s.end() );
  r = ads(t, r, orange(dst)).first;
  t << is_true<assert>( dst.empty() ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "10", std::string(r.begin(), r.end()) ) << s << FAS_TESTING_FILE_LINE;
}

UNIT(wspace_test, "parse space wide char")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;
  ad_space ads;
  std::wstring s = L"";
  typedef random_access_range<std::wstring::const_iterator> range_type;
  range_type r( s.begin(), s.end() );
  t << is_true<assert>(!r) << "0" ;
  r = ads(t, r);
  t << is_true<assert>(!r) << "1" ;

  s = L"\t/* \t aaa */ /*<*/ 10";
  r = range_type( s.begin(), s.end() );
  r = ads(t, r);
  t << equal<assert>( L"10", std::wstring(r.begin(), r.end()) ) << "\t/* \t aaa */ /*<*/ 10"  << FAS_TESTING_FILE_LINE;;
}

UNIT(copy_wspace_test, "copy parse space wide char")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;
  
  std::string dst;
  ad_space ads;
  std::wstring s = L"";
  typedef random_access_range<std::wstring::const_iterator> range_type;
  s = L"\t/* \t aaa */ /*<*/ 10";
  range_type r = range_type( s.begin(), s.end() );
  r = ads(t, r, orange(dst)).first;
  t << is_true<assert>( dst.empty() ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( L"10", std::wstring(r.begin(), r.end()) ) << "\t/* \t aaa */ /*<*/ 10"  << FAS_TESTING_FILE_LINE;;
  
}

UNIT(null_test, "parse null from file")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;

  {
    std::ofstream ofs("test_null.txt");
    ofs<<"null,4";
  }

  typedef std::istreambuf_iterator<char> iterator;
  typedef input_range< iterator, char > range_type;
  std::ifstream ifs("test_null.txt");
  range_type r = range_type( iterator(ifs), iterator() );

  ad_null an;
  r = an(t, r);
  std::string tail;
  std::copy( r.begin(), r.end(), std::back_inserter(tail) );
  t << equal<assert>( ",4", tail ) << ",4" << "!=" << tail<< FAS_TESTING_FILE_LINE;;
}

UNIT(copy_null_test, "copy parse null from file")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json::parse;

  typedef std::istreambuf_iterator<char> iterator;
  typedef input_range< iterator, char> range_type;
  std::ifstream ifs("test_null.txt");
  range_type r = range_type( iterator(ifs), iterator() );
  ad_null an;
  std::string result;
  r = an(t, r, orange(result) ).first;
  t << equal<assert>( result, std::string("null") ) << result << FAS_TESTING_FILE_LINE;
}

UNIT(bool_test, "parse bool")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json;
  using namespace fas::json::parse;

  ad_boolean ads;

  std::cout << "--1" << std::endl;
  std::string s = "true";
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = ads(t, r);
  t << is_true<assert>(!r) << "1"  << FAS_TESTING_FILE_LINE;;

  s = "false";
  r = range_type( s.begin(), s.end() );

  std::cout << "--2" << std::endl;
  r = ads(t, r);
  t << is_true<assert>(!r) << "2"  << FAS_TESTING_FILE_LINE;;

  try
  {
    std::cout << "--3" << std::endl;
    s = "fals";
    r = range_type( s.begin(), s.end() );
    r = ads(t, r);
    t << fail("expected unexpected_end_fragment")  << FAS_TESTING_FILE_LINE;
  }
  catch(const expected_of& )
  {
		std::cout << "catch(const fas::serialization::unexpected_end_fragment& )" << std::endl;
  }
}

UNIT(copy_bool_test, "copy parse bool")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json;
  using namespace fas::json::parse;

  ad_boolean ads;

  std::string s = "true";
  std::string result;
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );
  
  r = ads(t, r, orange(result) ).first;
  t << equal<assert>(result, s) << FAS_TESTING_FILE_LINE;

  s = "false";
  result.clear();
  r = range_type( s.begin(), s.end() );

  r = ads(t, r, orange(result) ).first;
  t << equal<assert>(result, s) << FAS_TESTING_FILE_LINE;
}

UNIT(number_test, "parse number")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json;
  using namespace fas::json::parse;

  ad_number ads;

  std::string s = "123456789 bla_bla";
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = ads(t, r);
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla_bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "-1.23E-123+1";
  r = range_type( s.begin(), s.end() );

  r = ads(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( "+1", tail ) << FAS_TESTING_FILE_LINE;
}

UNIT(copy_number_test, "parse number")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json;
  using namespace fas::json::parse;

  ad_number ads;

  std::string s = "123456789 bla_bla";
  std::string result;
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = ads(t, r, orange(result) ).first;
  std::string tail(r.begin(), r.end());
  t << equal<assert>( std::string("123456789"), result ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( std::string(" bla_bla"), tail ) << FAS_TESTING_FILE_LINE;

  s = "-1.23E-123+1";
  r = range_type( s.begin(), s.end() );

  result.clear();
  r = ads(t, r, orange(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( std::string("-1.23E-123"), result ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "+1", tail ) << tail;
}

UNIT(string_test, "parse string")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json;
  using namespace fas::json::parse;

  ad_string ads;

  std::string s = "\"\" bla-bla";
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = ads(t, r);
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "\"hello мир! \\uABCD \\u1F9D \\\" 'один \t\r\n \b \f \" bla-bla";
  r = range_type( s.begin(), s.end() );

  r = ads(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
}

UNIT(copy_string_test, "copy parse string")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json;
  using namespace fas::json::parse;

  ad_string ads;

  std::string s = "\"\" bla-bla";
  std::string result;
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = ads(t, r, orange(result) ).first;
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "\"\"", result ) << "["<< result << "]"<< FAS_TESTING_FILE_LINE;

  result.clear();
  s = "\"hello мир! \\uABCD \\u1F9D \\\" 'один \t\r\n \b \f \" bla-bla";
  r = range_type( s.begin(), s.end() );
 
  r = ads(t, r, orange(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "\"hello мир! \\uABCD \\u1F9D \\\" 'один \t\r\n \b \f \"", result ) << FAS_TESTING_FILE_LINE;
}

UNIT(simple_string_test, "parse simple string")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json;
  using namespace fas::json::parse;

  ad_simple_string ads;

  std::string s = "\"\" bla-bla";
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = ads(t, r);
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;

  s = "\"hello мир! \\uABCD \\u1F9D 'один \t\r\n \b \f \" bla-bla-bla";
  r = range_type( s.begin(), s.end() );

  r = ads(t, r);
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla-bla", tail ) << FAS_TESTING_FILE_LINE;
}

UNIT(copy_simple_string_test, "copy parse simple string")
{
  using namespace fas;
  using namespace fas::testing;
  using namespace fas::json;
  using namespace fas::json::parse;

  ad_simple_string ads;

  std::string s = "\"\" bla-bla";
  std::string result;
  typedef random_access_range<std::string::const_iterator> range_type;
  range_type r( s.begin(), s.end() );

  r = ads(t, r, orange(result) ).first;
  std::string tail(r.begin(), r.end());
  t << equal<assert>( " bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "\"\"", result ) << "["<< result << "]"<< FAS_TESTING_FILE_LINE;

  result.clear();
  s = "\"hello мир! \\uABCD \\u1F9D 'один \t\r\n \b \f \" bla-bla-bla";
  r = range_type( s.begin(), s.end() );

  r = ads(t, r, orange(result) ).first;
  tail = std::string(r.begin(), r.end());
  t << equal<assert>( " bla-bla-bla", tail ) << FAS_TESTING_FILE_LINE;
  t << equal<assert>( "\"hello мир! \\uABCD \\u1F9D 'один \t\r\n \b \f \"", result ) << FAS_TESTING_FILE_LINE;
  
}


BEGIN_SUITE(basic_parser_suite, "basic json parser suite")
  ADD_UNIT(space_test)
  ADD_UNIT(copy_space_test)
  ADD_UNIT(wspace_test)
  ADD_UNIT(copy_wspace_test)
  ADD_UNIT(null_test)
  ADD_UNIT(copy_null_test)
  ADD_UNIT(bool_test)
  ADD_UNIT(copy_bool_test)
  ADD_UNIT(number_test)
  ADD_UNIT(copy_number_test)
  ADD_UNIT(string_test)
  ADD_UNIT(copy_string_test)
  ADD_UNIT(simple_string_test)
  ADD_UNIT(copy_simple_string_test)
  ADD_ADVICE( ::fas::json::_except_, ::fas::json::ad_except)
  ADD_ASPECT( ::fas::json::parse::aspect_space )
END_SUITE(basic_parser_suite)
