#ifndef FAS_SERIALIZATION_JSON_EXCEPT_PARSE_ERROR_HPP
#define FAS_SERIALIZATION_JSON_EXCEPT_PARSE_ERROR_HPP

#include <fas/serialization/json/except/json_error.hpp>

namespace fas{ namespace json{

class parse_error: public json_error
{
public:
  typedef json_error::size_type size_type;
  
  parse_error(size_type tail_of = 0)
    : json_error("parse error", tail_of) {}
};

}}

#endif
