//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_COMMON_EXCEPT_OUT_OF_RANGE_HPP
#define FAS_SERIALIZATION_COMMON_EXCEPT_OUT_OF_RANGE_HPP

#include <fas/serialization/common/except/common_error.hpp>
#include <string>


namespace fas{ namespace serialization{

class out_of_range
  : public common_error
{
public:
  typedef common_error::size_type size_type;
  
  out_of_range(size_type tail_of = 0)
    : common_error( "out of range", tail_of) {}
    
  out_of_range(const std::string& str, size_type tail_of = 0)
   : common_error( std::string("out of range: ") + str, tail_of ) {}
   
};


}}

#endif
