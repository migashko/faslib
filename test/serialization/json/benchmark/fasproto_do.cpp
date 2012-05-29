#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <fas/serialization/json/deserializer.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/typemanip/tstring.hpp>

#include "test1.pb.h"
#include "benchmark.hpp"
  

#include <iostream>

namespace aj = ::fas::json;


FAS_NAME(id)
FAS_NAME(name)
FAS_NAME(email)

typedef aj::mem_fun_set_static<benchmark::Person, ::google::protobuf::int32, &benchmark::Person::set_id> mem_fun_id;
typedef aj::mem_fun_set_static<benchmark::Person, const ::std::string&, &benchmark::Person::set_name> mem_fun_name;
typedef aj::mem_fun_set_static<benchmark::Person, const ::std::string&, &benchmark::Person::set_email> mem_fun_email;

template<> int mem_fun_id::value = 0;
template<> std::string mem_fun_name::value = std::string();
template<> std::string mem_fun_email::value = std::string();

typedef aj::object<
  fas::type_list_n<
    aj::field< n_id, aj::setter< mem_fun_id, aj::integer > >,
    aj::field< n_name, aj::setter< mem_fun_name, aj::string >  >,
    aj::field< n_email, aj::setter< mem_fun_email, aj::string >  >
  >::type
> fasproto_json;

buffer_type buffer = "{\"id\":100,\"name\":\"Name\",\"email\":\"email@example.com\"}";


int main()
{
  mem_fun_name::value.reserve(100);
  mem_fun_email::value.reserve(100);
  benchmark::Person t;
  t.set_id(100);
  t.set_name("Name");
  t.set_email("email@example.com");

  aj::deserializer<> ds;
  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP; ++i)
  {
    *( ds( fasproto_json(), t, fas::range(buffer) ) )='\0';
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start;
  std::clog << std::endl
            << t.id() << std::endl
            << t.name() << std::endl
            << t.email() << std::endl;

  return 0;
}
