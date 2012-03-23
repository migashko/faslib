#ifndef FAS_SERIALIZATION_JSON_EXCEPT_EXPECTED_OF_HPP
#define FAS_SERIALIZATION_JSON_EXCEPT_EXPECTED_OF_HPP

#include <fas/serialization/json/except/json_error.hpp>
#include <string>

namespace fas{ namespace json{

class expected_of
  : public json_error
{
public:
  typedef json_error::size_type size_type; 
  expected_of(const std::string& str, size_type tail_of = 0)
    : json_error( std::string("expected of '") + str + std::string("'"), tail_of) {}
};


}}

#endif
