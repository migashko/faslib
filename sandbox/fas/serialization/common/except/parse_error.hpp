//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_COMMON_EXCEPT_PARSE_ERROR_HPP
#define FAS_SERIALIZATION_COMMON_EXCEPT_PARSE_ERROR_HPP

#include <fas/serialization/common/except/common_error.hpp>

namespace fas{ namespace serialization{

class parse_error: public common_error
{
public:
  typedef common_error::size_type size_type;
  
  parse_error(size_type tail_of = 0)
    : common_error("parse error", tail_of) {}
};

}}

#endif
