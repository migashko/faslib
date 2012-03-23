#include <fas/typemanip/tstring.hpp>

#include <string>
#include <iostream>
using namespace ::fas;

int main()
{
  if ( std::string()!=separator<>()() )
    return 1;
  if ( std::string("a")!=separator<'a'>()() )
    return 1;
  if ( std::string("ab")!=separator<'a', 'b'>()() )
    return 1;
  if ( std::string("abc")!=separator<'a', 'b', 'c'>()() )
    return 1;
  if ( std::string("abcd")!=separator<'a', 'b', 'c', 'd'>()() )
    return 1;
  if ( std::string("abcde")!=separator<'a', 'b', 'c', 'd', 'e'>()() )
    return 1;
  if ( std::wstring()!=wseparator<>()() )
    return 1;
  if ( std::wstring(L"a")!=wseparator< L'a'>()() )
    return 1;
  if ( std::wstring(L"ab")!=wseparator< L'a', L'b'>()() )
    return 1;
  if ( std::wstring(L"abc")!=wseparator< L'a', L'b', L'c'>()() )
    return 1;
  if ( std::wstring(L"abcd")!=wseparator< L'a', L'b', L'c', L'd'>()() )
    return 1;
  if ( std::wstring(L"abcde")!=wseparator< L'a', L'b', L'c', L'd', L'e'>()() )
    return 1;
  return 0;
}



