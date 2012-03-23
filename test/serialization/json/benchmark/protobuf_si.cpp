#include <fas/range.hpp>
#include <fas/xtime.hpp>

#include "test1.pb.h"
#include "benchmark.hpp"
#include <iostream>

buffer_type buffer;

int main()
{
  benchmark::Person t;
  
  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP * 10; ++i)
  {
    t.set_id(100);
    t.set_name("Name");
    t.set_email("email@example.com");
    t.SerializeToArray(buffer, MAX_BUF);
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << ( finish - start )/10 ;
  return 0;
}
