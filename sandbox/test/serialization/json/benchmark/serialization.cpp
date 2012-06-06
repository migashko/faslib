#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <fas/typemanip/tstring.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/advice.hpp>
#include <fas/aop/aspect_class.hpp>

#include <fas/serialization/json/ser/ad_integer.hpp>
#include <fas/serialization/json/ser/ad_array.hpp>
#include <fas/serialization/json/ser/ad_sequence.hpp>
#include <fas/serialization/json/ser/ad_attr.hpp>
#include <fas/serialization/json/ser/ad_string.hpp>
#include <fas/serialization/json/ser/ad_field.hpp>
#include <fas/serialization/json/ser/ad_object.hpp>
#include <fas/serialization/json/ser/ad_stub.hpp>
#include <fas/serialization/json/ser/ad_field.hpp>
#include <fas/serialization/json/ser/ad_field_list.hpp>


#include <fas/serialization/json/meta/object.hpp>
#include <fas/serialization/json/meta/field.hpp>
#include <fas/serialization/json/meta/integer.hpp>
#include <fas/serialization/json/meta/attr.hpp>
#include <fas/type_list/type_list_n.hpp>
//#include <fas/serialization/json/serializer.hpp>

#include </home/migashko/distr/json_spirit_v4/json_spirit/json_spirit_writer_template.h>
#include "test1.pb.h"


///home/migashko/distr/protobuf-2.4.1/src
#include </home/migashko/distr/protobuf-2.4.1/src/google/protobuf/io/zero_copy_stream.h>
#include </home/migashko/distr/protobuf-2.4.1/src/google/protobuf/io/zero_copy_stream_impl_lite.h>
#include </home/migashko/distr/protobuf-2.4.1/src/google/protobuf/text_format.h>

#include <cstring>
#include <iostream>
#include <iterator>
#include <vector>

using namespace fas;
namespace aj = ::fas::json;
namespace ajs = ::fas::json::ser;
using namespace json_spirit;

#define LIMIT_OP 10000000/*0*/


struct json_serializer_aspect
  : aspect<
      type_list_n<
        advice< ajs::_string_, ajs::ad_string>,
        advice< ajs::_cstring_, ajs::ad_cstring>,
        advice< ajs::_integer_, ajs::ad_integer>,
        advice< ajs::_field_, ajs::ad_field>,
        advice< ajs::_field_, ajs::ad_field>,
        advice< ajs::_field_list_, ajs::ad_field_list>,
        advice< ajs::_array_, ajs::ad_array>,
        advice< ajs::_sequence_, ajs::ad_sequence>,
        advice< ajs::_object_, ajs::ad_object>,
        advice< ajs::_stub_, ajs::ad_stub>
      >::type
  >
{};


class json_serializer
  : public aspect_class<json_serializer_aspect>
{
public:
  template<typename M, typename V, typename R>
  R operator()(const M& m, const V& v, R r)
  {
    typedef typename M::serializer_tag serializer_tag; 
    return this->get_aspect().template get<serializer_tag>()(*this, m, v, r);
  }
};


FAS_NAME(field1)
FAS_NAME(field2)

FAS_NAME(f1)
FAS_NAME(f2)

struct test1
{
  int field1;
  int field2;
};

typedef
  aj::object<
    type_list_n<
      aj::attr< n_f1, aj::field<test1, int, &test1::field1, aj::integer/*<int>*/ > >,
      aj::attr< n_f2, aj::field<test1, int, &test1::field2, aj::integer/*<int>*/ > >
    >::type
  > test1_json;
  
#define MAX_BUF 1024
char buffer[MAX_BUF];
std::stringstream ss;

inline void memcpy_buff()
{
  test1 t;
  t.field1 = 100;
  t.field2 = -100000000;
  // *(reinterpret_cast<test1*>(buffer)) = t;
  std::memcpy( &t, buffer, sizeof(t) );
}

inline void proto_buff()
{
  test::test1 t;
  t.set_field1(100);
  t.set_field2(-100000000);
  t.SerializeToArray(buffer, MAX_BUF);
  
}

inline void sprintf_buff()
{
  test1 t;
  t.field1 = 100;
  t.field2 = -100000000;
  sprintf(buffer, "%d %d", t.field1, t.field2);
}

inline void js_ss()
{
  test1 t;
  t.field1 = 100;
  t.field2 = -100000000;
  ss.seekp(0);
  ss << t.field1 << " " <<  t.field2;
}

inline void json_spirit_buff()
{
  /*test1 t;
  t.field1 = 100;
  t.field2 = -100000000;*/

  Object addr_obj(2);
  addr_obj.push_back( Pair("f1", 100 ) );
  addr_obj.push_back( Pair("f2", -100000000 ) );
  Value val( addr_obj );
  ss.seekp(0);
  write_stream( val, ss);
}

inline void fas_buff()
{
  test1 t;
  t.field1 = 100;
  t.field2 = -100000000;
  json_serializer jsser;
  jsser( test1_json(), t, (buffer, buffer + MAX_BUF) );
}




void delay(time_t nanotm)
{
  nanospan start = process_nanotime();
  while ( process_nanotime() - start < nanospan(0, nanotm) );
};


void show(nanospan start, nanospan finish)
{
  std::cout << finish - start << std::endl;
  std::cout << LIMIT_OP*rate(finish - start) << std::endl;
}

#include <iterator>
void back_inserter_test()
{
  nanospan start;
  nanospan finish;

  const long M = 1024*1024*100;
  char *t = new char[M];
  std::vector<char> v;
  std::back_insert_iterator< std::vector<char> > itr = std::back_inserter(v);
  start = process_nanotime();
  for (int i = 0; i < M;++i)
    *(itr++) = i;
  finish = process_nanotime();
  std::cout << "back_inserter " << M << std::endl;
  std::cout << "size = " << v.size() << std::endl;
  std::cout << finish - start  << std::endl;
  delete[] t;
};

void inserter_test()
{
  nanospan start;
  nanospan finish;

  const long M = 1024*1024*100;
  char *t = new char[M];
  std::vector<char> v;
  std::insert_iterator< std::vector<char> > itr = std::inserter(v, v.end());
  start = process_nanotime();
  for (int i = 0; i < M;++i)
    *(itr++) = i;
  finish = process_nanotime();
  std::cout << "inserter " << M << std::endl;
  std::cout << "size = " << v.size() << std::endl;
  std::cout << finish - start  << std::endl;
  delete[] t;
};

int main()
{
  back_inserter_test();
  inserter_test();
  back_inserter_test();
  inserter_test();
  return 0;
  test::test1 t;
  t.set_field1(100);
  t.set_field2(-100000000);

  google::protobuf::io::ArrayOutputStream aos(buffer, MAX_BUF);
  google::protobuf::TextFormat::Print(t, &aos);
  std::string sss;
  google::protobuf::TextFormat::PrintToString(t, &sss);
  std::cout << "[" << ss << "]"<< std::endl; 
  char *data;
  int s;
  aos.Next((void**)&data, &s);
  std::cout << "[" << std::string( data, data + s ) << "]"<< std::endl; 
  std::cout << s << " ------------------------------ " << std::endl;

  enum { temp = has_metatype<int>::value };
  nanospan start;
  nanospan finish;

  std::cout << "fas_buff " << LIMIT_OP << std::endl;
  start = process_nanotime();
  for ( int i = 0 ; i < LIMIT_OP; ++i)
    fas_buff();
  finish = process_nanotime();
  show(start, finish);

  std::cout << "memcpy_buff " << LIMIT_OP << std::endl;
  start = process_nanotime();
  for ( int i = 0 ; i < LIMIT_OP; ++i)
    memcpy_buff();
  finish = process_nanotime();
  show(start, finish);
  
  std::cout << "proto_buff " << LIMIT_OP << std::endl;
  start = process_nanotime();
  for ( int i = 0 ; i < LIMIT_OP; ++i)
    proto_buff();
  finish = process_nanotime();
  show(start, finish);

  std::cout << "sprintf_buff " << LIMIT_OP << std::endl;
  start = process_nanotime();
  for ( int i = 0 ; i < LIMIT_OP; ++i)
    sprintf_buff();
  finish = process_nanotime();
  show(start, finish);

  std::cout << "js_ss " << LIMIT_OP << std::endl;
  start = process_nanotime();
  for ( int i = 0 ; i < LIMIT_OP; ++i)
    js_ss();
  finish = process_nanotime();
  show(start, finish);

  std::cout << "json_spirit " << LIMIT_OP << std::endl;
  start = process_nanotime();
  for ( int i = 0 ; i < LIMIT_OP; ++i)
    json_spirit_buff();
  finish = process_nanotime();
  show(start, finish);



  

/*
  test1 t1;
  typedef range_traits<char*>::type range_type;
  range_type r = (buffer, buffer + MAX_BUF);

  std::stringstream ss2;
  typedef output_range< std::ostreambuf_iterator<char> > range_type2;
  range_type2 r2 = (std::ostreambuf_iterator<char>(ss2) );
  std::ostreambuf_iterator<char> aa(ss2);
  *r2 = '1';
  *(r2++) = '1';
  json_serializer jsser;
  test1_json tj;
  start = process_nanotime();
  for ( int i = 0 ; i < LIMIT_OP; ++i)
    fas_buff();
  finish = process_nanotime();
  show(start, finish);
  start = process_nanotime();
  for ( int i = 0 ; i < LIMIT_OP; ++i)
  {
    t1.field1 = i%100;
    t1.field2 = (i+1)%100;
    sprintf(buffer, "%d %d", t1.field1, t1.field2);
  }
  finish = process_nanotime();
  show(start, finish);
  
  Object addr_obj;

  addr_obj.push_back( Pair( n_f1()(), t1.field1 ) );
  addr_obj.push_back( Pair( n_f2()(), t1.field2 ) );
  
  Value val( addr_obj );

  std::stringstream ss;
  start = process_nanotime();
  for ( int i = 0 ; i < LIMIT_OP; ++i)
  {
    addr_obj[0].value_ = t1.field1;
    addr_obj[1].value_ = t1.field2;
    ss.seekp(0);
    write_stream( val, ss);
    
    t1.field1 = i%100;
    t1.field2 = (i+1)%100;
    sprintf(buffer, "%d %d", t1.field1, t1.field2);
    
  }
  finish = process_nanotime();
  show(start, finish);
  */

  return 0;
}
