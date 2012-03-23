#include <fas/range.hpp>
#include <fas/xtime.hpp>

#include "benchmark.hpp"
#include <sstream>
#include <iostream>



int main()
{
  Person2 t;
  t.id = 100;
  t.set_name("Name");
  t.set_email("email@example.com");

  std::stringstream ss;
  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    ss.seekp(0);
    ss << t.id << " " << t.name << " " << t.email;
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog << std::endl << ss.str() << std::endl;

  return 0;
}
