//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/algorithm/nothing.hpp>
#include <fas/algorithm/transform.hpp>
#include <fas/algorithm/transform_if.hpp>
#include <fas/typemanip.hpp>
#include <fas/integral.hpp>
#include <fas/mp.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;

typedef type_list_n<
	char, 
	int,
	long,
	double
>::type list1;

typedef type_list_n<
  type2type<char>,
  type2type<int>,
  type2type<long>,
  type2type<double>
>::type list2;

int main()
{
  typedef transform<list1, type2type<_1> >::type result_type;
 
  enum { result = static_check< same_type<result_type, list2>::value>::value
  };
  
  
  
  return 0;
}


