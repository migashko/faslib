#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/meta.hpp>


#include "test1.pb.h"
#include "benchmark.hpp"
  

#include <iostream>

namespace aj = ::fas::json;

typedef aj::array<
  fas::type_list_n<
    aj::getter< benchmark::Person, ::google::protobuf::int32, &benchmark::Person::id, aj::integer >,
    aj::getter< benchmark::Person, const ::std::string&, &benchmark::Person::name, aj::string >,
    aj::getter< benchmark::Person, const ::std::string&, &benchmark::Person::email, aj::string >
  >::type
> fasproto_array_json;

buffer_type buffer;

int main()
{
  benchmark::Person t;
  t.set_id(100);
  t.set_name("Name");
  t.set_email("email@example.com");

  aj::serializer<> s;

  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    *( s( fasproto_array_json(), t, fas::range(buffer) ) )='\0';
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog << buffer << std::endl;;
  return 0;
}
