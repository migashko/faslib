//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_UNIT_COUNTS_HPP
#define FAS_TESTING_UNIT_COUNTS_HPP

#include <fas/testing/counts.hpp>

namespace fas{ namespace testing{

struct unit_counts 
  : counts
{
  int statements;
  unit_counts()
    : counts()
    , statements()
  {}

  void operator += ( const unit_counts & c )
  {
    counts::operator += (c);
    statements += c.statements;
  }
};

}}

#endif
