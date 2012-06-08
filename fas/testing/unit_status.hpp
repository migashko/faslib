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
  typedef enum {
    noerror,
    trace,
    error,
    fail,
    fatal
  } type;
};

}}


#endif

