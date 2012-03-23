#ifndef FAS_SERIALIZATION_JSON_EXCEPT_INVALID_JSON_NUMBER_HPP
#define FAS_SERIALIZATION_JSON_EXCEPT_INVALID_JSON_NUMBER_HPP

#include <fas/serialization/json/except/invalid_json.hpp>

namespace fas{ namespace json{

class invalid_json_number: public invalid_json
{ 
public:
  typedef invalid_json::size_type size_type; 
  invalid_json_number(size_type tail_of = 0)
    : invalid_json("invalid json number", tail_of)  {}
};


}}

#endif
