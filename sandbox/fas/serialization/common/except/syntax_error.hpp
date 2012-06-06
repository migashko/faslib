//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_COMMON_EXCEPT_SYNTAX_ERROR_HPP
#define FAS_SERIALIZATION_COMMON_EXCEPT_SYNTAX_ERROR_HPP

#include <fas/serialization/common/except/common_error.hpp>
#include <string>

namespace fas{ namespace serialization{

class syntax_error: public common_error
{
public:
  typedef common_error::size_type size_type;

  syntax_error(size_type tail_of = 0)
    : common_error("invalid json", tail_of)  {}
    
  syntax_error(const std::string& str, size_type tail_of = 0)
   : common_error( str, tail_of ) {}

};


}}

#endif
