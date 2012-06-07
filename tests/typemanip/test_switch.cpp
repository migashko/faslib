//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/typemanip.hpp>
#include <fas/static_check.hpp>

#include <fas/typemanip/switch_.hpp>
#include <fas/typemanip/case_.hpp>
#include <fas/typemanip/default_.hpp>

#include <string>

using namespace ::fas;


int main()
{
  typedef switch_<
      case_c<0, char>,
      case_c<0, short>,
      case_c<1, std::string>,
      case_c<0, int>,
      case_c<1, long>
  >::type result1;
  
  typedef switch_<
      case_c<0, char>,
      case_c<0, short>
  >::type result2;
  
  typedef switch_<
    case_c<0, char>
  >::type result3;

  typedef switch_<
    case_c<2, char>
  >::type result4;

  typedef switch_<
    case_c<0, char>,
    default_<int>
  >::type result5;

  enum {
    result = static_check< some_type<result1, std::string>::value >::value
             + static_check< some_type<result2, empty_type>::value >::value
             + static_check< some_type<result3, empty_type>::value >::value
             + static_check< some_type<result4, char>::value >::value
             + static_check< some_type<result5, int>::value >::value
  };
  return 0;
}



