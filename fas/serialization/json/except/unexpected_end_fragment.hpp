#ifndef FAS_SERIALIZATION_JSON_EXCEPT_UNEXPECTED_END_FRAGMENT_HPP
#define FAS_SERIALIZATION_JSON_EXCEPT_UNEXPECTED_END_FRAGMENT_HPP

#include <fas/serialization/json/except/json_error.hpp>
#include <string>

namespace fas{ namespace json{

class unexpected_end_fragment
  : public json_error
{
public:
  typedef json_error::size_type size_type;
  
  unexpected_end_fragment(size_type tail_of = 0)
    : json_error( "unexpected end of fragment", tail_of) {}
  unexpected_end_fragment(const std::string& str, size_type tail_of = 0)
   : json_error( str, tail_of ) {}
};


}}

#endif
