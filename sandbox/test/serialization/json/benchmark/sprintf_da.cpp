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

  char buff[] = "100 Name email@example.com";
  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    sscanf(buff, "%d %s %s", &(t.id), t.name, t.email);
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog << std::endl
            << t.id << std::endl
            << t.name << std::endl
            << t.email << std::endl;


  return 0;
}
