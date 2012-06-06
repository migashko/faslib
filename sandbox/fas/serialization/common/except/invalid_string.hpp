//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_COMMON_EXCEPT_INVALID_STRING_HPP
#define FAS_SERIALIZATION_COMMON_EXCEPT_INVALID_STRING_HPP

#include <fas/serialization/common/except/syntax_error.hpp>

namespace fas{ namespace serialization{

class invalid_string: public syntax_error
{ 
public:
  typedef syntax_error::size_type size_type; 
  invalid_string(size_type tail_of = 0)
    : syntax_error("invalid string", tail_of)  {}
};


}}

#endif
