#include <fas/range.hpp>
#include <fas/xtime.hpp>

#include "benchmark.hpp"
#include <string>
#include <iostream>

#include "json_spirit/json_spirit_reader_template.h"

namespace js = json_spirit;


int main()
{
  std::stringstream ss;
  js::Object person(3);
  js::Value val;
  std::string str = "{\"id\":100,\"name\":\"Name\",\"email\":\"email@example.com\"}";

  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP / 10; ++i)
  {
    ss.seekg(0);
    js::read_string( str, val);
    person = val.get_obj();
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << ( finish - start ) * 10 ;
  std::clog << std::endl << person[0].value_.get_int()<< std::endl << person[1].value_.get_str() << std::endl << person[2].value_.get_str() << std::endl << person.size() << std::endl;

  return 0;
}
