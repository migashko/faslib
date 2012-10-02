//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/testing/unit.hpp>
#include <fas/static_check/static_check.hpp>

using namespace fas;

UNIT(foo_test, "foo testing")
{

}

int main()
{

  enum {
    result =
      static_check<
        some_type<
          foo_test_type_list::left_type::advice_class,
          foo_test_unit
        >::value
      >::value
      +
      static_check<
        some_type<
          foo_test_type_list::left_type::tag,
          foo_test
        >::value
      >::value
      +
      static_check<
        some_type<
          foo_test_type_list::right_type::left_type::tag,
          testing::_units_
        >::value
      >::value
      +
      static_check<
        some_type<
          foo_test_type_list::right_type::left_type::target,
          type_list<foo_test>
        >::value
      >::value

  };
  foo_test_unit f;
  if ( f.name() != "foo_test") return -1;
  if ( f.desc() != "foo testing") return -1;

  return 0;
}

