//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_TESTING_HPP
#define FAS_TESTING_TESTING_HPP

#include <fas/testing/suite_counts.hpp>
#include <fas/system/colorized.hpp>
#include <iostream>

namespace fas{ namespace testing{

inline void show_total_result( const suite_counts& sc )
{
  if (!sc)
    std::cout << ::fas::light_red ;
  else
    std::cout << ::fas::green ;
  
  std::cout << "**************************************" << std::endl;
  std::cout << "units: " << sc.units << std::endl;
  if (!sc)
  {
    std::cout << ::fas::red  << "units fails: " << sc.units-sc.units_passed << ::fas::light_red  << std::endl;
  }
  
  std::cout << "statements: " << sc.statements << std::endl;
  if (!sc)
  {
    if (sc.errors!=0) std::cout << ::fas::red ;
    std::cout << "errors: " << sc.errors << ::fas::light_red << std::endl;
    if (sc.fails!=0) std::cout << ::fas::red ;
    std::cout << "fails: " << sc.fails << ::fas::light_red << std::endl;
    if (sc.fatals!=0) std::cout << ::fas::red ;
    std::cout << "fatals: " << sc.fatals << ::fas::light_red << std::endl;
  }
  std::cout << "**************************************" << std::endl;
  std::cout << ::fas::restore ;
  std::cout << std::endl;
}


}}


#define BEGIN_TEST ::fas::testing::suite_counts fas_testing(int argc, char* argv[]) { ::fas::testing::suite_counts sc;
#define RUN_SUITE(name) ::fas::testing::suite_counts name##_suite_run(int argc, char* argv[]); sc+=name##_suite_run(argc, argv);
#define END_TEST show_total_result(sc); return sc;}

#endif
