#include <fas/range.hpp>
#include <fas/xtime.hpp>

#include "benchmark.hpp"
#include <sstream>
#include <iostream>

#include "json_spirit/json_spirit_writer_template.h"

namespace js = json_spirit;

int main()
{
  std::stringstream ss;
  //std::string ss;
  fas::nanospan start = fas::process_nanotime();

  js::Object person(3);
  person[0].name_ = "id";
  person[0].value_ = 100;
  person[1].name_ = "name";
  person[1].value_ = "Name";
  person[2].name_ = "email";
  person[2].value_ = "email@example.com";
  js::Value val( person );

  for (size_t i = 0; i < TOTAL_OP / 10; ++i)
  {
    ss.seekp(0);
    js::write_stream( val, ss, js::raw_utf8);
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << ( finish - start ) * 10;
  std::clog << std::endl << ss.str() << std::endl;
  
  return 0;
}
