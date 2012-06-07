//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <iostream>
#include <fas/testing.hpp>
#include <fas/range.hpp>
#include <fas/static_check/static_check.hpp>
#include <string>
#include <list>

UNIT(container_range_unit, "")
{
  using namespace ::fas::testing;
  typedef std::list<int> list_type;
  list_type lst;
  for (int i = 0; i < 10; i++)
    lst.push_back(i);
  typedef fas::typerange<list_type>::reverse_range reverse_range;
  reverse_range rr = fas::rrange(lst);
  for (int i = 0; i < 10; i++)
    t << equal<expect>( *rr++, 9 - i ) << FAS_TESTING_FILE_LINE;
};


BEGIN_SUITE(container_range_suite, "")
  ADD_UNIT(container_range_unit)
END_SUITE(container_range_suite)
