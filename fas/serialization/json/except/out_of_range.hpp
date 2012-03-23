#ifndef FAS_SERIALIZATION_JSON_EXCEPT_OUT_OF_RANGE_HPP
#define FAS_SERIALIZATION_JSON_EXCEPT_OUT_OF_RANGE_HPP

#include <fas/serialization/json/except/json_error.hpp>
#include <string>


namespace fas{ namespace json{

class out_of_range
  : public json_error
{
public:
  typedef json_error::size_type size_type;
  
  out_of_range(size_type tail_of = 0)
    : json_error( "out of range", tail_of) {}
    
  out_of_range(const std::string& str, size_type tail_of = 0)
   : json_error( std::string("out of range: ") + str, tail_of ) {}
   
};


}}

#endif
