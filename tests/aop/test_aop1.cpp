//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/aop/advice.hpp>
#include <fas/aop/aspect.hpp>
#include <fas/aop/private/has_tag.hpp>
#include <fas/aop/private/is_has_tag.hpp>
#include <fas/aop/private/is_advice.hpp>
#include <fas/aop/private/aspect_select.hpp>

#include <fas/static_check/static_check.hpp>
#include <fas/integral/int_.hpp>
#include <fas/typemanip/type2type.hpp>
#include <fas/type_list/length.hpp>
#include <fas/algorithm/find_if.hpp>


using namespace fas;

struct _tag_;

struct test_aspect1: aspect<
    type_list_n<
      advice< int_<1>, int_<1> >,
      advice< int_<2>, int_<2> >,
      advice< int_<3>, int_<3> >,
      advice< _tag_, type2type<_tag_> >
    >::type
  >
{};

struct test_aspect2: aspect<
    type_list_n<
      advice< int_<3>, int_<33> >,
      advice< int_<4>, int_<4> >,
      advice< int_<5>, int_<5> >,
      test_aspect1
    >::type
  >
{};

struct test_aspect3: aspect<
    type_list_n<
      advice< int_<6>, int_<6> >,
      advice< int_<7>, int_<7> >,
      advice< int_<5>, int_<55> >,
      test_aspect2
    >::type
  >
{};

typedef aspect_select<test_aspect3, is_advice< a< _1 > > >::type result;


int main()
{

  enum
  {
      value = static_check< length<result>::value == 10 >::value
              + static_check<
                  some_type<
                    int_<55>,
                    find_if<
                      result,
                      some_type< has_tag<_1>, int_<5> >
                    >::type::advice_class
                  >::value
                >::value

  };

  return 0;
}


