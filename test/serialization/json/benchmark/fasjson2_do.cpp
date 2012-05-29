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
    aj::field< n_id, aj::attr< Person2, int, &Person2::id, aj::integer > >,
    aj::field< n_name,aj::attr< Person2, Person2::name_type, &Person2::name, aj::string > >,
    aj::field< n_email,aj::attr< Person2, Person2::email_type, &Person2::email, aj::string > >
  >::type
> Person2_json;

buffer_type buffer = "{\"id\":100,\"name\":\"Name\",\"email\":\"email@example.com\"}";
//buffer_type buffer = "{\"email\":\"email@example.com\",\"name\":\"Name\",\"id\":100}";

int main()
{
  Person2 t;

  aj::deserializer<> ds;

  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    ds( Person2_json(), t, fas::range(buffer) );
  }

  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog << std::endl
            << t.id << std::endl
            << t.name << std::endl
            << t.email << std::endl;


  return 0;
}
