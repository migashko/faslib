#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/meta.hpp>
#include "benchmark.hpp"
#include <iostream>

namespace aj = ::fas::json;

buffer_type buffer;

int main()
{
  Person2 t;
  t.id = 100;
  t.set_name("Name");
  t.set_email("email@example.com");

  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    sprintf(buffer, "id=%d name=%s email=%s", t.id, t.name, t.email);
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog << std::endl << buffer << std::endl;

  return 0;
}
