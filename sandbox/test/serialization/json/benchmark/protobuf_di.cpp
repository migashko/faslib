#include <fas/range.hpp>
#include <fas/xtime.hpp>

#include "test1.pb.h"
#include "benchmark.hpp"
#include <iostream>

buffer_type buffer;

int main()
{
  Person p;
  benchmark::Person t;
  t.set_id(100);
  t.set_name("Name");
  t.set_email("email@example.com");
  size_t bufsize = t.SerializeToArray(buffer, MAX_BUF);
  
  t = benchmark::Person();
  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP * 10; ++i)
  {
    t.ParseFromArray(buffer, bufsize);
    p.id = t.id();
    p.name = t.name();
    p.email = t.email();
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << ( finish - start )/10 ;
  std::clog << std::endl
            << p.id << std::endl
            << p.name << std::endl
            << p.email << std::endl;

  return 0;
}
