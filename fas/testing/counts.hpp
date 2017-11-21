//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_COUNTS_HPP
#define FAS_TESTING_COUNTS_HPP

namespace fas{ namespace testing{

struct counts
{
  int  errors;
  int  fails;
  int  fatals;
  bool crash;

  counts()
    : errors()
    , fails()
    , fatals()
    , crash()
  {}
  
  void operator += ( const counts& c )
  {
    errors += c.errors;
    fails  += c.fails;
    fatals += c.fatals;
    if ( c.crash )
      crash = true;
  }
  
  bool ok() const
  {
    return errors==0 && fails==0 && fatals==0 && crash==false;
  }
  
};

}}

#endif
