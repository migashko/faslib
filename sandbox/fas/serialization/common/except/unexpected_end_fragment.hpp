//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_COMMON_EXCEPT_UNEXPECTED_END_FRAGMENT_HPP
#define FAS_SERIALIZATION_COMMON_EXCEPT_UNEXPECTED_END_FRAGMENT_HPP

#include <fas/serialization/common/except/syntax_error.hpp>
#include <string>

namespace fas{ namespace serialization{

class unexpected_end_fragment
  : public syntax_error
{
public:
  typedef syntax_error::size_type size_type;
  
  unexpected_end_fragment(size_type tail_of = 0)
    : syntax_error( "unexpected end of fragment", tail_of) {}
    
  unexpected_end_fragment(const std::string& str, size_type tail_of = 0)
   : syntax_error( str, tail_of ) {}
};


}}

#endif
