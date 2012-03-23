#include <fas/range.hpp>
#include <fas/xtime.hpp>

#include "benchmark.hpp"
#include <sstream>
#include <iostream>

#include "jsoncpp/json/json.h"

//namespace aj = ::fas::json;
// namespace js = json_spirit;


int main()
{
  Json::Value person;
  Json::FastWriter writer;
  person["id"] = 100;
  person["name"] = "Name";
  person["email"] = "email@example.com";

  std::stringstream ss;
  fas::nanospan start = fas::process_nanotime();

  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    /*
    ss.seekp(0);
    person["id"] = 100;
    person["name"] = "Name";
    person["email"] = "email@example.com";
    
    ss <<*/ writer.write( person );
    // 
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start << std::endl;
  std::cout << ss.str() << std::endl;
/*
  Person2 t;
  t.id = 100;
  t.set_name("My Name");
  t.set_email("email@example.com");

  std::stringstream ss;
  fas::nanospan start = fas::process_nanotime();

  
  js::Object person(3);
  person[0].name_ = "id";
  person[0].value_ = 100;
  person[1].name_ = "name";
  person[1].value_ = "Name";
  person[2].name_ = "email";
  person[2].value_ = "email@example.com";
  js::Value val( person );

  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    ss.seekp(0);
    js::write_stream( val, ss, js::raw_utf8);
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start << std::endl;
  std::cout << ss.str() << std::endl;
  */
  
  return 0;
}
