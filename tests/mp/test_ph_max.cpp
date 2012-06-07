//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/mp/placeholders.hpp>
#include <fas/mp/ph_max.hpp>
#include <fas/type_list/type_list_n.hpp>
#include <fas/static_check.hpp>
#include <fas/typemanip/some_type.hpp>

using namespace ::fas;

template<typename>
struct test1{};

template<typename, typename>
struct test2{};

template<typename, typename, typename>
struct test3{};

template<typename, typename, typename, typename>
struct test4{};

template<typename, typename, typename, typename, typename>
struct test5{};

int main()
{
  

  enum
  {
    result = static_check< ph_max<int >::value == 0  >::value
           + static_check< ph_max<_1>::value == 1  >::value
           + static_check< ph_max< test1<_2> >::value == 2  >::value
           + static_check< ph_max< test1<test1<_5> > >::value == 5  >::value
           + static_check< ph_max< _ >::value == 1  >::value
           + static_check< ph_max< test1<test1<_> > >::value == 1  >::value
           + static_check< ph_max< test2< int, test1<_3> > >::value == 3  >::value
           + static_check< ph_max< test2< test1<_4>, int > >::value == 4  >::value
           + static_check< ph_max< test2< _, _ > >::value == 2  >::value
           + static_check< ph_max< test2< _, test1<_> > >::value == 2  >::value
           + static_check< ph_max< test2< _4, test1<_> > >::value == 4  >::value
           + static_check< ph_max< test2< _, test2<_, test1<_> > > >::value == 3  >::value
           
           + static_check< ph_max< test3< _, _1, _ > >::value == 2  >::value
           + static_check< ph_max< test3< _, _, _ > >::value == 3  >::value
           + static_check< ph_max< test3< _4, _, _ > >::value == 4  >::value
           
           + static_check< ph_max< test4< _, _, _3, _ > >::value == 3  >::value
           + static_check< ph_max< test4< _, _, _, _1 > >::value == 3  >::value
           + static_check< ph_max< test4< _5, _, _, _1 > >::value == 5  >::value
           
           + static_check< ph_max< test5< _, _, _, _, _> >::value == 5  >::value
           + static_check< ph_max< test5< _, _1, _, _, _> >::value == 4  >::value
           + static_check< ph_max< test5< _5, _2, _3, _1, _4> >::value == 5  >::value
           + static_check< ph_max< test5< _1, _, _1, _, _> >::value == 3  >::value
  };
  
  return 0;
}


