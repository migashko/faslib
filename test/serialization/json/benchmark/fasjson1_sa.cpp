#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/meta.hpp>
#include "benchmark.hpp"
#include <iostream>
namespace aj = ::fas::json;

typedef aj::array<
  fas::type_list_n<
    aj::attr< Person, int, &Person::id, aj::integer >,
    aj::attr< Person, std::string, &Person::name, aj::string >,
    aj::attr< Person, std::string, &Person::email, aj::string >
  >::type
> Person_array_json;

buffer_type buffer;

int main()
{
  Person t;
  t.id = 100;
  t.name = "Name";
  t.email = "email@example.com";

  aj::serializer<> s;

  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    *( s( Person_array_json(), t, fas::range(buffer) ) )='\0';
  }

  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog  << std::endl << buffer << std::endl;

  return 0;
}
