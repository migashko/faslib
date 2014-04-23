//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TESTING_UNIT_STATUS_HPP
#define FAS_TESTING_UNIT_STATUS_HPP

namespace fas{ namespace testing{

struct unit_status
{
  enum type_tag{
    noerror,
    trace,
    error,
    fail,
    fatal
  };
  
  typedef type_tag type;
};

}}


#endif

