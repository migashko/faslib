#include <fas/testing.hpp>

#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/sequence.hpp>
#include <fas/serialization/json/meta/string.hpp>
#include <fas/serialization/json/deser/ad_integer.hpp>
#include <fas/serialization/json/deser/ad_string.hpp>
#include <fas/serialization/json/deser/ad_separator.hpp>

#include <fas/serialization/json/deser/ad_sequence.hpp>
#include <fas/serialization/json/deser/deserialize_sequence.hpp>
#include <fas/serialization/json/deser/deserialize_integer.hpp>
#include <fas/range/range.hpp>
#include <fas/typemanip/tstring.hpp>

#include <vector>
#include <string>

#include <fas/serialization/json/parser/aspect.hpp>

struct f_int
{
  template<typename V, typename R>
  R operator()( V& value, R r)
  {
    using namespace ::fas::json;
    return deserialize_integer( value, r);
  }
};

UNIT(sequence_deserialize_test, "test sequence_deserialize function")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  
  std::string value;
  std::vector<int> result;
  deserialize_sequence(  orange(result), range(value), f_int() );
  t << equal<expect>(result, std::vector<int>()) << FAS_TESTING_FILE_LINE;


  value="0";
  result.clear();
  deserialize_sequence(  orange(result), range(value), f_int() );
  t << equal<assert, int>(result.size(), 1) << FAS_TESTING_FILE_LINE;
  t << equal<expect, int>(result[0], 0 ) << FAS_TESTING_FILE_LINE;

  value="0,-1";
  result.clear();
  deserialize_sequence(  orange(result), range(value), f_int() );
  t << equal<assert, int>(result.size(), 2) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[0], 0 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], -1 ) << FAS_TESTING_FILE_LINE;

  value="0,-1,1000";
  result.clear();
  deserialize_sequence(  orange(result), range(value), deserialize_integer<int, typerange<std::string>::range> );
  t << equal<assert, int>(result.size(), 3) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[0], 0 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[2], 1000 ) << FAS_TESTING_FILE_LINE;
}


UNIT(ad_sequence_test, "test ad_sequence advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  std::string value;
  std::vector<int> result;
  ad_sequence ads;
  
  ads(t, sequence<integer>(), result, range(value) );
  t << equal<expect>(result, std::vector<int>()) << FAS_TESTING_FILE_LINE;


  value=" 0 ";
  result.clear();
  ads(t, sequence<integer>(), result, range(value) );
  t << equal<assert, int>(result.size(), 1) << FAS_TESTING_FILE_LINE 
    << stop;
  t << equal<expect>(result[0], 0 ) << FAS_TESTING_FILE_LINE;

  value=" 0 , -1 ";
  result.clear();
  ads(t, sequence<integer>(), result, range(value) );
  t << equal<assert, int>(result.size(), 2) << FAS_TESTING_FILE_LINE
    << stop;
    
  t << equal<expect>(result[0], 0 )    << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], -1 )   << FAS_TESTING_FILE_LINE;

  value=" 0, -1 ,1000";
  result.clear();
  ads(t, sequence<integer>(), result, range(value) );
  t << equal<assert, int>(result.size(), 3) << FAS_TESTING_FILE_LINE
    << stop;
  t << equal<expect>(result[0], 0 )    << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], -1 )   << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[2], 1000 ) << FAS_TESTING_FILE_LINE;
  
  value=" false,0, \"\", -1 , {}, 1000";
  result.clear();
  ads(t, sequence<integer>(), result, range(value) );
  t << equal<assert, int>(result.size(), 3) << FAS_TESTING_FILE_LINE 
    << stop;
  t << equal<expect>(result[0], 0 )    << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], -1 )   << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[2], 1000 ) << FAS_TESTING_FILE_LINE;

  // null десериализуеться! 
  value=" null,0, \"\", -1 , {}, 1000";
  result.clear();
  ads(t, sequence< /*sequence<*/integer/*>*/ >(), result, range(value) );
  t << equal<assert, int>(result.size(), 4) << FAS_TESTING_FILE_LINE
    << stop;
  t << equal<expect>(result[0], 0 )    << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], 0 )    << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[2], -1 )   << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[3], 1000 ) << FAS_TESTING_FILE_LINE;
}

UNIT(ad_sequence_test2, "test ad_sequence advice")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  std::string value;
  int result[10]={1};


  ad_sequence ads;
  ads(t, sequence<integer>(), result, range(value) );
  t << equal<expect>(result[0], 1 ) << FAS_TESTING_FILE_LINE;


  value=" 0 ";
  std::fill_n(result, 10, 0);
  ads(t, sequence<integer>(), result, range(value) );
  t << equal<expect>(result[0], 0 ) << FAS_TESTING_FILE_LINE;

  value=" 0 , -1 ";
  std::fill_n(result, 10, 0);
  ads(t, sequence<integer>(), result, range(value) );
  t << equal<expect>(result[0], 0 )  << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], -1 ) << FAS_TESTING_FILE_LINE;

  value=" 0, -1 ,1000";
  std::fill_n(result, 10, 0);
  ads(t, sequence<integer>(), result, range(value) );
  t << equal<expect>(result[0], 0 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], -1 ) << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[2], 1000 ) << FAS_TESTING_FILE_LINE;
  
  value=" false,0, \"\", -1 , {}, 1000";
  std::fill_n(result, 10, 0);
  ads(t, sequence<integer>(), result, range(value) );
  t << equal<expect>(result[0], 0 )    << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], -1 )   << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[2], 1000 ) << FAS_TESTING_FILE_LINE;

  // null десериализуеться! 
  value=" null,0, \"\", -1 , {}, 1000";
  std::fill_n(result, 10, 0);
  ads(t, sequence< /*sequence<*/integer/*>*/ >(), result, range(value) );
  t << equal<expect>(result[0], 0 )    << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[1], 0 )    << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[2], -1 )   << FAS_TESTING_FILE_LINE;
  t << equal<expect>(result[3], 1000 ) << FAS_TESTING_FILE_LINE;

    
  /*int *ptr = result;
  ads(t, sequence<integer>(), ptr, range(value) );
  */
  
  

}

UNIT(ad_sequence_test3, "test ad_sequence advice for arrays")
{
  using namespace ::fas;
  using namespace ::fas::testing;
  using namespace ::fas::json;
  using namespace ::fas::json::deser;

  //std::vector< char[20] > value;
  char result[4][20]={"11111", "22222", "33333", "44444"};
  std::string jsonstring = "\"aa\",\"bbb\",\"cccc\"";
  ad_sequence ads;
  ads( t, sequence<string>(), result, range(jsonstring) );
  
  t << equal<expect, std::string>(result[0], "aa" )    << FAS_TESTING_FILE_LINE;
  t << equal<expect, std::string>(result[1], "bbb" )    << FAS_TESTING_FILE_LINE;
  t << equal<expect, std::string>(result[2], "cccc" )    << FAS_TESTING_FILE_LINE;
  t << equal<expect, std::string>(result[3], "" )    << FAS_TESTING_FILE_LINE;
  
  int matrix[4][4]={ {1,1,1,1}, {2,2,2,2}, {3,3,3,3}, {4,4,4,4} };
  jsonstring = "1,2,3,4,5,6,7,8,9,10,11";
  ads( t, sequence< sequence<integer> >(), matrix, range(jsonstring) );
  for (int i =0 ; i < 11; ++i)
    t << equal<expect>(i+1, matrix[i/4][i%4] )  << "[" << i+1 << "!=" << matrix[i/4][i%4] << "] " <<  FAS_TESTING_FILE_LINE;

  for (int i =11 ; i < 16; ++i)
    t << equal<expect>(0, matrix[i/4][i%4] )  << "[" << i << "] " <<  FAS_TESTING_FILE_LINE;

}

BEGIN_SUITE(sequence_deserialize_suite, "sequence deserializer suite")
  
  ADD_UNIT(sequence_deserialize_test)
  ADD_UNIT(ad_sequence_test)
  ADD_UNIT(ad_sequence_test2)
  ADD_UNIT(ad_sequence_test3)
  ADD_ADVICE( ::fas::json::deser::_integer_, ::fas::json::deser::ad_integer)
  ADD_ADVICE( ::fas::json::deser::_sequence_, ::fas::json::deser::ad_sequence)
  ADD_ADVICE( ::fas::json::deser::_string_, ::fas::json::deser::ad_string)
  ADD_ADVICE( ::fas::json::deser::_quotes_,  ::fas::json::deser::ad_quotes)
  ADD_ASPECT(::fas::json::parse::aspect)
  
END_SUITE(sequence_deserialize_suite)
