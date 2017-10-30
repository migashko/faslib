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

UNIT(unit0, "testing unit 0")
{
  //t << is_true<crash>( false ) << "is_true<expect>( true ) first";
  t << is_true<expect>( true ) << "is_true<expect>( true ) first";
  t << is_true<expect>( true ) << "is_true<expect>( true ) second";
  t << is_true<expect>( true ) << "is_true<expect>( true ) third";
  t << warning( "warning" );
  t << message( "message" );
}

UNIT(unit1, "testing unit 1")
{
  t << is_true<expect>( false ) << "is_true<expect>( false ) first";
  t << is_true<expect>( false ) << "is_true<expect>( false ) second";
  t << is_true<expect>( false ) << "is_true<expect>( false ) third";
}

UNIT(unit2, "testing unit 2")
{
  t << is_true<expect>( false ) << "is_true<expect>( false ) first";
  t << is_true<assert>( false ) << "is_true<assert>( false ) second";
  t << stop; // assert abort unit
  t << is_true<assert>( false ) << "is_true<assert>( false ) third";
}

UNIT(unit3, "testing unit 3")
{
  t << is_true<expect>( false ) << "is_true<assert>( false ) first";
  t << is_true<critical>( false ) << "is_true<critical>( false ) second";
  t << stop; // critical abort test
  t << is_true<assert>( false ) << "is_true<assert>( false ) third";
}

UNIT(unit4, "testing unit 4 (SKIP THIS)")
{
  t << is_true<expect>( false ) << "is_true<expect>( false ) first";
  t << is_true<expect>( false ) << "is_true<expect>( false ) second";
  t << is_true<expect>( false ) << "is_true<expect>( false ) third";
}

UNIT(unit5, "testing unit 5 (SKIP THIS)")
{
  t << nothing;
  
}

BEGIN_SUITE(suite1, "suite example description" )
  ADD_UNIT(unit0)
  ADD_UNIT(unit1)
  ADD_UNIT(unit2)
  ADD_UNIT(unit3)
  ADD_UNIT(unit4)
  ADD_UNIT(unit5)
END_SUITE(suite1)


int main(int argc, char* argv[])
{
  using namespace ::fas::testing;
  suite_counts fas_suite1_suite_run(int argc, char* argv[]);
  suite_counts result = fas_suite1_suite_run(argc, argv);
  std::cout << MESSAGE << "---------------------------------" << std::endl;
  std::cout << MESSAGE << "Total " << result.units_total << std::endl;
  std::cout << MESSAGE << "Passed " << result.units_passed << std::endl;
  std::cout << MESSAGE << "Skipped " << result.units_skip << std::endl;
  std::cout << MESSAGE << "Statements " << result.statements << std::endl;
  std::cout << MESSAGE << "Errors " << result.errors << std::endl;
  std::cout << MESSAGE << "Fails " << result.fails << std::endl;
  std::cout << MESSAGE << "Fatals " << result.fatals << std::endl;
  
  std::cout << MESSAGE << "suite unit list size = " << fas_suite1_suite::size() << std::endl;
  return !(result.units_passed==1 && result.units_total == 4 && result.units_skip==2 && result.statements==10);
}

