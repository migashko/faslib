#include <fas/mp/placeholders.hpp>
#include <fas/mp/ps.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/static_check.hpp>
#include <fas/typemanip/some_type.hpp>

using namespace ::fas;

typedef type_list_n<int, char, long>::type list;

int main()
{
  

  enum
  {
    result = static_check< some_type< float, ps<float, list>::type >::value >::value
             + static_check< some_type< int, ps<_1, list>::type >::value >::value
             + static_check< some_type< char, ps<_2, list>::type >::value >::value
             + static_check< some_type< long, ps<_3, list>::type >::value >::value
             + static_check< some_type< int, ps<_, list>::type >::value >::value
             + static_check< some_type< long, ps<_, list, int_<2> >::type >::value >::value
    
  };
  
  return 0;
}


