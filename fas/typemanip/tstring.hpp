//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_TSTRING_HPP
#define FAS_TYPEMANIP_TSTRING_HPP

#include <fas/typemanip/metalist.hpp>

#define FAS_NAME(N) struct n_##N{ typedef fas::metalist::tstring metatype; typedef const char* value_type; value_type operator()() const { return #N; } };
#define FAS_WNAME(N) struct n_##N{ typedef fas::metalist::tstring metatype; typedef const wchar_t* value_type; value_type operator()() const { return L#N; } };

#define FAS_STRING(N, S) struct N{ typedef fas::metalist::tstring metatype; typedef const char* value_type; value_type operator()() const { return S; } };
#define FAS_WSTRING(N, S) struct N{ typedef fas::metalist::tstring metatype; typedef const wchar_t* value_type; value_type operator()() const { return S; } };

template< typename C, C ch0=C(), C ch1=C(), C ch2=C(), C ch3=C(), C ch4=C()>
struct separator_t
{
  typedef fas::metalist::tstring metatype; 
  typedef const C* value_type;
  value_type operator()() const 
  {
    static const C result[]={ch0, ch1, ch2, ch3, ch4, C()};
    return result; 
  } 
};


template< char ch0=char(), char ch1=char(), char ch2=char(), char ch3=char(), char ch4=char()>
struct separator
  : separator_t<char, ch0, ch1, ch2, ch3, ch4>
{
};

template< wchar_t ch0=wchar_t(), wchar_t ch1=wchar_t(), wchar_t ch2=char(), wchar_t ch3=wchar_t(), wchar_t ch4=wchar_t()>
struct wseparator
  : separator_t<wchar_t, ch0, ch1, ch2, ch3, ch4>
{
};

#endif

