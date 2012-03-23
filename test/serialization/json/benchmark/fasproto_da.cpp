#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <fas/serialization/json/deserializer.hpp>
#include <fas/serialization/json/meta.hpp>


#include "test1.pb.h"
#include "benchmark.hpp"
  

#include <iostream>

namespace aj = ::fas::json;

typedef aj::array<
  fas::type_list_n<
    aj::setter< benchmark::Person, ::google::protobuf::int32, &benchmark::Person::set_id, aj::integer >,
    aj::setter< benchmark::Person, const ::std::string&, &benchmark::Person::set_name, aj::string >,
    aj::setter< benchmark::Person, const ::std::string&, &benchmark::Person::set_email, aj::string >
  >::type
> fasproto_array_json;

buffer_type buffer = "[100,\"Name\",\"email@example.com\"]";


int main()
{
  benchmark::Person t;
  t.set_id(100);
  t.set_name("Name");
  t.set_email("email@example.com");

  aj::deserializer<> ds;
  
  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    *( ds( fasproto_array_json(), t, fas::range(buffer) ) )='\0';
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog << std::endl
            << t.id() << std::endl
            << t.name() << std::endl
            << t.email() << std::endl;
 return 0;
}
