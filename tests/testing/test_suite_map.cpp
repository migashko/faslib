//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/testing/suite.hpp>
#include <fas/testing/unit.hpp>
#include <fas/testing/statements.hpp>
#include <fas/static_check/static_check.hpp>
#include <sstream>
#include <iostream>

using namespace fas;
using namespace fas::testing;

UNIT(unit1, "testing unit 1")
{
  t << is_true<expect>( false ) << "is_true<expect>( false ) first";
  t << is_true<expect>( false ) << "is_true<expect>( false ) second";
  t << is_true<expect>( false ) << "is_true<expect>( false ) third";
}

UNIT(unit2, "testing unit 2")
{
  t << is_true<expect>( false ) << "is_true<expect>( false ) first";
  t << is_true<expect>( false ) << "is_true<expect>( false ) second";
  t << is_true<expect>( false ) << "is_true<expect>( false ) third";
}

UNIT(unit3, "testing unit 3")
{
  t << is_true<expect>( false ) << "is_true<assert>( false ) first";
  t << is_true<critical>( false ) << "is_true<assert>( false ) second";
  t << is_true<assert>( false ) << "is_true<assert>( false ) third";
}

UNIT(unit4, "testing unit 4")
{
  t << is_true<expect>( false ) << "is_true<expect>( false ) first";
  t << is_true<expect>( false ) << "is_true<expect>( false ) second";
  t << is_true<expect>( false ) << "is_true<expect>( false ) third";
}


BEGIN_SUITE(suite1, "suite example description" )
  ADD_UNIT(unit1)
  ADD_UNIT(unit2)
  ADD_UNIT(unit3)
  ADD_UNIT(unit4)
END_SUITE(suite1)


int main(int argc, char* argv[])
{
  using namespace ::fas::testing;
  suite_counts fas_suite1_suite_run(int argc, char* argv[]);
  suite_counts result = fas_suite1_suite_run(argc, argv);
  std::cout << MESSAGE << "result.units=" << result.units << " result.units_total=" << result.units_total << std::endl;
  return !(result.units==2 && result.units_total == 4);
}

