#include <fas/typemanip.hpp>
#include <fas/static_check.hpp>

#include <fas/integral/int_.hpp>
#include <fas/typemanip/switch_.hpp>
#include <fas/typemanip/case_.hpp>
#include <fas/type_list/type_list_n.hpp>

#include <string>

using namespace ::fas;


int main()
{
  typedef switch_<
    type_list_n<
      case_<int_<0>, char>,
      case_c<0, short>,
      case_<int_<1>, std::string>,
      case_c<0, int>,
      case_c<1, long>
    >::type
  >::type result1;
  
  typedef switch_<
    type_list_n<
      case_<int_<0>, char>,
      case_c<0, short>
    >::type
  >::type result2;
  
  typedef switch_<
    case_<int_<0>, char>
  >::type result3;

  typedef switch_<
    case_<int_<2>, char>
  >::type result4;
  
  enum {
    result = static_check< some_type<result1, std::string>::value >::value
             + static_check< some_type<result2, empty_type>::value >::value
             + static_check< some_type<result3, empty_type>::value >::value
             + static_check< some_type<result4, char>::value >::value
  };
  return 0;
}



