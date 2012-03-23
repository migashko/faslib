#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/meta.hpp>

#include "benchmark.hpp"
  
#define MAX_BUF 1024
#include <iostream>

namespace aj = ::fas::json;

char buffer[MAX_BUF];


typedef aj::array<
  fas::type_list_n<
    aj::attr< Person, int, &Person::id, aj::integer >,
    aj::attr< Person, std::string, &Person::name, aj::string >,
    aj::attr< Person, std::string, &Person::email, aj::string >
  >::type
> array_json;

int main()
{
  Person t;
  t.id = 100;
  t.name = "My Name";
  t.email = "email@example.com";

  aj::serializer<> s;
  //span_list sl;
  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP/*/ONE_TIME_OP*/; ++i)
  {
    *( s( array_json(), t, fas::range(buffer) ) )='\0';
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start << std::endl;
  std::cout << buffer << std::endl;
  //std::cout << benchmark(sl) /** static_cast<long>( sl.size() )*/ << std::endl;
  return 0;
}
