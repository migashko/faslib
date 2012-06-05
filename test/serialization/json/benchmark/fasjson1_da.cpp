#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <fas/serialization/json/deserializer.hpp>
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


buffer_type buffer = "[100,\"Name\",\"email@example.com\"]";

int main()
{
  Person t;

  aj::deserializer<> ds;

  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    ds( Person_array_json(), t, fas::range(buffer) );
  }

  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog << std::endl
            << t.id << std::endl
            << t.name << std::endl
            << t.email << std::endl;


  return 0;
}
