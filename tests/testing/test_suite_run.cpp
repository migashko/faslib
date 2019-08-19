//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/testing/suite.hpp>
#include <fas/testing/unit.hpp>
#include <fas/testing/statements.hpp>
#include <fas/static_check/static_check.hpp>
#include <fas/system/nullptr.hpp>
#include <sstream>

using namespace fas;
using namespace fas::testing;

bool test_run0();
bool test_run1();
bool test_run2();

bool test_run0()
{
  std::stringstream ss, sst;
  suite<> su(ss);
  su.run(0, fas_nullptr);
  std::cout << ss.str() << std::endl;
  sst << "[ --BEG-- ] 0 tests." << std::endl
      << "[ --END-- ] " <<std::endl
      << "[ PASSED  ] 0 tests." << std::endl;
  if ( ss.str() != sst.str() ) 
  {
    std::cout << FAS_FL << std::endl;
    return false;
  }
  
  if ( su.size() != 0) 
  {
    std::cout << FAS_FL << std::endl;
    return false;
  }
  
  if ( su.errors() != 0) 
  {
    std::cout << FAS_FL << std::endl;
    return false;
  }
  
  if ( su.fails() != 0) 
  {
    std::cout << FAS_FL << std::endl;
    return false;
  }
  
  if ( su.fatals() != 0) 
  {
    std::cout << FAS_FL << std::endl;
    return false;
  }
  return true;
}

UNIT(unit1, "unit1 testing")
{
  t << nothing;
}

typedef aspect<
  type_list_n<
    fas_unit1_type_list
  >::type
> suite_aspect1;

bool test_run1()
{
  std::stringstream ss, sst;
  suite< suite_aspect1 > su(ss);
  su.run(0, fas_nullptr);

  std::cout << ss.str() << std::endl;
  sst << "[ --BEG-- ] 1 tests."<< std::endl
      << "[ RUN     ] unit1"<< std::endl
      << "[      OK ] " << std::endl
      << "[ --END-- ] " <<std::endl
      << "[ PASSED  ] 1 tests." << std::endl;
  if ( ss.str() != sst.str() ) 
  {
    std::cout << std::endl << "Expected: " << std::endl << sst.str() << std::endl;
    return false;
  }
  if ( su.size() != 1) return false;
  if ( su.errors() != 0) return false;
  if ( su.fails() != 0) return false;
  if ( su.fatals() != 0) return false;

  return true;
}

UNIT(unit2, "unit2 testing")
{
  t << message("hello");
}



typedef aspect<
  type_list_n<
    fas_unit1_type_list,
    fas_unit2_type_list
  >::type
> suite_aspect2;

bool test_run2()
{
  std::stringstream ss, sst;
  suite< suite_aspect2 > su(ss);
  su.run(0, fas_nullptr);
  std::cout << ss.str() << std::endl;
  sst << "[ --BEG-- ] 2 tests."<< std::endl
      << "[ RUN     ] unit1"<< std::endl
      << "[      OK ] " << std::endl
      << "[ RUN     ] unit2"<< std::endl
      << "[ MESSAGE ] hello"<< std::endl
      << "[      OK ] " << std::endl
      << "[ --END-- ] " << std::endl
      << "[ PASSED  ] 2 tests." << std::endl;

  if ( ss.str() != sst.str() ) return false;
  if ( su.size() != 2) return false;
  if ( su.errors() != 0) return false;
  if ( su.fails() != 0) return false;
  if ( su.fatals() != 0) return false;
  return true;
}

int main()
{
  if (!test_run0()) return -1;
  if (!test_run1()) return -2;
  if (!test_run2()) return -3;
  return 0;
}

