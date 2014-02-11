//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/type_list.hpp>
#include <fas/static_check.hpp>

using namespace ::fas;

struct list_1 : type_list<char, type_list<long> > {};
struct list_2 : type_list<float, type_list<int> > {};


typedef type_list<char, type_list<long, list_2 > > check_list1;
typedef push_front<list_1, list_2>::type result_list;

int main()
{
  enum
  {
    test = static_check< same_type< check_list1, result_list>::value >::value
  };

  return 0;
}

