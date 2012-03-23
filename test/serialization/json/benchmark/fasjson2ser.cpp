#include <fas/range.hpp>
#include <fas/xtime.hpp>
#include <fas/serialization/json/serializer.hpp>
#include <fas/serialization/json/meta.hpp>

#include <fas/serialization/json/except/ad_emptyexcept.hpp>
#include <fas/serialization/json/except/ad_noexcept.hpp>

#include "benchmark.hpp"
  
#define MAX_BUF 1024
#include <iostream>

namespace aj = ::fas::json;

buffer_type buffer;


typedef aj::array<
  fas::type_list_n<
    aj::attr< Person2, int, &Person2::id, aj::integer >,
    aj::attr< Person2, Person2::name_type, &Person2::name, aj::string >,
    aj::attr< Person2, Person2::email_type, &Person2::email, aj::string >
  >::type
> array_json;


struct except_aspect: fas::aspect< fas::type_list_n<
  fas::advice< aj::_except_, aj::ad_except >,
  fas::del< aj::ser::_block_ >
>::type > { };
// struct except_aspect: fas::aspect< fas::advice< aj::_except_, aj::ad_emptyexcept > > { };
// struct except_aspect: fas::aspect< fas::advice< aj::_except_, aj::ad_noexcept > > { };

int main()
{
  Person2 t;
  t.id = 100;
  t.set_name("My Name");
  t.set_email("email@example.com");

  
  fas::range_traits<buffer_type>::range r = fas::range( buffer );
  aj::serializer< except_aspect > s;
  std::cout << "sizeof: " << sizeof(s) << std::endl;
  
  //span_list sl;
  fas::nanospan start = fas::process_nanotime();
  for (size_t i = 0; i < TOTAL_OP/*/ONE_TIME_OP*/; ++i)
  {
    //*( s( array_json(), t, fas::range(buffer) ) )='\0';
    s( array_json(), t, r );
  }
  fas::nanospan finish = fas::process_nanotime();
  std::cout << finish - start << std::endl;
  std::cout << buffer << std::endl;
  //std::cout << benchmark(sl) /** static_cast<long>( sl.size() )*/ << std::endl;
  return 0;
}
