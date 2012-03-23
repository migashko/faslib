#include <iostream>
#include <fas/range/.hpp>
#include <fas/serialization/json/meta.hpp>
#include <fas/serialization/json/deser/deserializer.hpp>
#include <iterator>
namespace aj = ::fas::json;


int main()
{
  /*fas::range_traits<std::ostreambuf_iterator<char> >::range_type r = 
    fas::( std::ostreambuf_iterator<char>(std::cout) );
    */
  /*
  std::ostreambuf_iterator<char> oitr(std::cout);
  aj::deser::deserializer<>()(
    aj::string(),
    oitr,
    fas::( std::istreambuf_iterator<char>(std::cin), std::istreambuf_iterator<char>() ) 
  );
  */
  return 0;
}