//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011, 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_SRANGE_HPP
#define FAS_RANGE_SRANGE_HPP

#include <fas/range/random_access_range.hpp>
#include <cstring>

namespace fas{

inline random_access_range<char*> srange(char* str)
{
  return random_access_range<char*>(str, str + std::strlen(str) );
}

inline random_access_range<const char*> srange(const char* str)
{
  return random_access_range<const char*>(str, str + std::strlen(str) );
}

}

#endif
