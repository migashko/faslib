#ifndef FAS_SERIALIZATION_JSON_EXCEPT_INVALID_JSON_STRING_HPP
#define FAS_SERIALIZATION_JSON_EXCEPT_INVALID_JSON_STRING_HPP

#include <fas/serialization/json/except/invalid_json.hpp>

namespace fas{ namespace json{

class invalid_json_string: public invalid_json
{ 
public:
  typedef invalid_json::size_type size_type;
  
  invalid_json_string(size_type tail_of = 0)
    : invalid_json("invalid json string", tail_of)  {}
};

}}

#endif
