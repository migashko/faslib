#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <fas/serialization/json/deserializer.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/typemanip/tstring.hpp>
#include "benchmark.hpp"
#include <iostream>
namespace aj = ::fas::json;

FAS_NAME(id)
FAS_NAME(name)
FAS_NAME(email)

typedef aj::object<
  fas::type_list_n<
    aj::member< n_id, aj::attr< Person, int, &Person::id, aj::integer > >,
    aj::member< n_name,aj::attr< Person, std::string, &Person::name, aj::string > >,
    aj::member< n_email,aj::attr< Person, std::string, &Person::email, aj::string > >
  >::type
> Person_json;

buffer_type buffer = "{\"id\":100,\"name\":\"Name\",\"email\":\"email@example.com\"}";
//buffer_type buffer = "{\"email\":\"email@example.com\",\"name\":\"Name\",\"id\":100}";

int main()
{
  Person t;

  aj::deserializer<> ds;

  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    ds( Person_json(), t, fas::range(buffer) );
  }

  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog << std::endl
            << t.id << std::endl
            << t.name << std::endl
            << t.email << std::endl;


  return 0;
}
