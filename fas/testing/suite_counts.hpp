//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_SUITE_COUNTS_HPP
#define FAS_TESTING_SUITE_COUNTS_HPP

#include <fas/testing/unit_counts.hpp>

namespace fas{ namespace testing{

struct suite_counts
  : unit_counts
{
  int units;
  int units_total;
  int units_passed;
  
  suite_counts()
    : unit_counts()
    , units()
    , units_total()
    , units_passed()
  {
  }
  
  void operator += ( const suite_counts& c )
  {
    unit_counts::operator += (c);
    units += c.units;
    units_total += c.units_total;
    units_passed += c.units_passed;
  }
  
  void operator += ( const unit_counts& c )
  {
    unit_counts::operator += (c);
  }
  
  operator bool () const
  {
    return units - units_passed == 0;
  }
};

  
}}

#endif
