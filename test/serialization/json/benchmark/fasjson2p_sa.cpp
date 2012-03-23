#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/meta.hpp>
#include "benchmark.hpp"
#include <iostream>
namespace aj = ::fas::json;

typedef aj::array<
  fas::type_list_n<
    aj::attr< Person2, int, &Person2::id, aj::integer >,
    aj::attr< Person2, Person2::name_type, &Person2::name, aj::string >,
    aj::attr< Person2, Person2::email_type, &Person2::email, aj::string >
  >::type
> Person2_array_json;

buffer_type buffer;

int main()
{
  Person2 t;
  t.id = 100;
  t.set_name("Name");
  t.set_name("email@example.com");

  aj::serializer<> s;

  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    *( s( Person2_array_json(), t, buffer ) )='\0';
  }

  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog  << std::endl << buffer << std::endl;

  return 0;
}
