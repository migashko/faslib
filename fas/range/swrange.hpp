//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2013
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_RANGE_SWRANGE_HPP
#define FAS_RANGE_SWRANGE_HPP

#include <fas/range/random_access_range.hpp>
#include <cwchar>

namespace fas{

inline random_access_range<wchar_t*> swrange(wchar_t* str)
{
  return random_access_range<wchar_t*>(str, str + std::wcslen(str) );
}

}

#endif
