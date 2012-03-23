#ifndef FAS_SERIALIZATION_JSON_EXCEPT_INVALID_JSON_HPP
#define FAS_SERIALIZATION_JSON_EXCEPT_INVALID_JSON_HPP

#include <fas/serialization/json/except/json_error.hpp>
#include <string>

namespace fas{ namespace json{

class invalid_json: public json_error
{
public:
  typedef json_error::size_type size_type;

  invalid_json(size_type tail_of = 0)
    : json_error("invalid json", tail_of)  {}
    
  invalid_json(const std::string& str, size_type tail_of = 0)
   : json_error( str, tail_of ) {}

};


}}

#endif
