#include <fas/range.hpp>
#include <fas/xtime.hpp>

#include "test1.pb.h"
#include "benchmark.hpp"
#include <iostream>

buffer_type buffer;

int main()
{
  benchmark::Person t;
  t.set_id(100);
  t.set_name("Name");
  t.set_email("email@example.com");
  
  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP * 10; ++i)
  {
    t.SerializeToArray(buffer, MAX_BUF);
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << ( finish - start )/10 ;
  std::clog << std::endl << "sizeof  Person: " << sizeof(t) << std::endl;
  return 0;
}
