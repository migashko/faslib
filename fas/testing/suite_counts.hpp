//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_SUITE_COUNTS_HPP
#define FAS_TESTING_SUITE_COUNTS_HPP

#include <fas/testing/unit_counts.hpp>
#include <iostream>
namespace fas{ namespace testing{

struct suite_counts
  : unit_counts
{
  int units_total;
  int units_passed;
  int units_skip;
  
  suite_counts()
    : unit_counts()
    , units_total()
    , units_passed()
    , units_skip() 
  {
  }
  
  void operator += ( const suite_counts& c )
  {
    unit_counts::operator += ( static_cast<const unit_counts&>(c) );
    this->units_total += c.units_total;
    std::cout << "-2-" << this->units_total << std::endl;
    this->units_passed += c.units_passed;
    this->units_skip += c.units_skip;
  }
  
  void operator += ( const unit_counts& c )
  {
    unit_counts::operator += (c);
    ++this->units_total;
    std::cout << "-1-" << this->units_total << std::endl;
    if ( c.ok() )
      ++this->units_passed;
  }
  
  bool ok() const
  {
    return unit_counts::ok();
    //return units - units_passed == 0;
  }
};

  
}}

#endif
