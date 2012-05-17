//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_TCHARS_HPP
#define FAS_TYPEMANIP_TCHARS_HPP

#include <fas/typemanip/metalist.hpp>

template< typename C, C ch0=C(), C ch1=C(), C ch2=C(), C ch3=C(), C ch4=C()
										, C ch5=C(), C ch6=C(), C ch7=C(), C ch8=C(), C ch9=C()	>
struct tchars_t
{
  typedef fas::metalist::tstring metatype; 
  typedef const C* value_type;
  value_type operator()() const 
  {
    static const C result[]={ ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9, C() };
    return result; 
  } 
};

template< char ch0=char(), char ch1=char(), char ch2=char(), char ch3=char(), char ch4=char(),
          char ch5=char(), char ch6=char(), char ch7=char(), char ch8=char(), char ch9=char()>
struct tchars
  : tchars_t<char, ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9>
{
};

template< wchar_t ch0=wchar_t(), wchar_t ch1=wchar_t(), wchar_t ch2=char(), wchar_t ch3=wchar_t(), wchar_t ch4=wchar_t(),
          wchar_t ch5=wchar_t(), wchar_t ch6=wchar_t(), wchar_t ch7=char(), wchar_t ch8=wchar_t(), wchar_t ch9=wchar_t()>
struct twchars
  : tchars_t<wchar_t, ch0, ch1, ch2, ch3, ch4, ch5, ch6, ch7, ch8, ch9>
{
};

#endif

