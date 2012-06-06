//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#include <fas/typemanip/tchars.hpp>

#include <string>
#include <iostream>
using namespace ::fas;

int main()
{
  if ( std::string()!=tchars<>()() )
    return 1;
  if ( std::string("a")!=tchars<'a'>()() )
    return 1;
  if ( std::string("ab")!=tchars<'a', 'b'>()() )
    return 1;
  if ( std::string("abc")!=tchars<'a', 'b', 'c'>()() )
    return 1;
  if ( std::string("abcd")!=tchars<'a', 'b', 'c', 'd'>()() )
    return 1;
  if ( std::string("abcde")!=tchars<'a', 'b', 'c', 'd', 'e'>()() )
    return 1;
  if ( std::wstring()!=twchars<>()() )
    return 1;
  if ( std::wstring(L"a")!=twchars< L'a'>()() )
    return 1;
  if ( std::wstring(L"ab")!=twchars< L'a', L'b'>()() )
    return 1;
  if ( std::wstring(L"abc")!=twchars< L'a', L'b', L'c'>()() )
    return 1;
  if ( std::wstring(L"abcd")!=twchars< L'a', L'b', L'c', L'd'>()() )
    return 1;
  if ( std::wstring(L"abcde")!=twchars< L'a', L'b', L'c', L'd', L'e'>()() )
    return 1;
  return 0;
}



