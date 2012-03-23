#include <fas/range.hpp>
#include <fas/xtime.hpp>

#include "benchmark.hpp"
#include <sstream>
#include <string>
#include <iostream>

#include "jsoncpp/json/json.h"

int main()
{
  Json::Value person;
  Json::FastWriter writer;
  person["id"] = 100;
  person["name"] = "Name";
  person["email"] = "email@example.com";

  std::string str;
  fas::nanospan start = fas::process_nanotime();

  for (size_t i = 0; i < TOTAL_OP / 10; ++i)
  {
    str =  writer.write( person );
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << ( finish - start ) * 10  ;
  std::clog << std::endl << str<< std::endl;
  return 0;
}
