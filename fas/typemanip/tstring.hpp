// Author: Vladimir Migashko <migashko@faslib.com>, (C) 2008, 2011
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_TYPEMANIP_TSTRING_HPP
#define FAS_TYPEMANIP_TSTRING_HPP

#include <fas/typemanip/metalist.hpp>
/**
 * string as template parameter
 * 
 * FAS_NAME(name):
 * 
 * struct n_name
 * {
 *   typedef const char* value_type;
 *   value_type operator()() const 
 *   {
 *     return "name";
 *   }
 * }
 * 
 * FAS_STRING(my_string, "my string"):
 * 
 * struct my_string
 * {
 *   typedef const char* value_type;
 *   value_type operator()() const 
 *   {
 *     return "my string";
 *   }
 * }
 * 
 */
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


/*
template<>
struct separator< 0, 0, 0, 0, 0>
{
  typedef fas::metalist::tstring metatype; 
  typedef const char* value_type;
  value_type operator()() const 
  {
    return ""; 
  } 
};

template<char ch0>
struct separator< ch0, 0, 0, 0, 0>
{
  typedef fas::metalist::tstring metatype; 
  typedef const char* value_type;
  value_type operator()() const 
  {
    const char result[]={ch0};
    return result; 
  } 
};

template<char ch0, char ch1>
struct separator< ch0, ch1, 0, 0, 0>
{
  typedef fas::metalist::tstring metatype; 
  typedef const char* value_type;
  value_type operator()() const 
  {
    const char result[]={ch0, ch1};
    return result; 
  } 
};

template<char ch0, char ch1, char ch2>
struct separator< ch0, ch1, ch2, 0, 0>
{
  typedef fas::metalist::tstring metatype; 
  typedef const char* value_type;
  value_type operator()() const 
  {
    const char result[]={ch0, ch1, ch2};
    return result; 
  } 
};

template<char ch0, char ch1, char ch2, char ch3>
struct separator< ch0, ch1, ch2, ch3, 0>
{
  typedef fas::metalist::tstring metatype; 
  typedef const char* value_type;
  value_type operator()() const 
  {
    const char result[]={ch0, ch1, ch2, ch3};
    return result; 
  } 
};

template<char ch0, char ch1, char ch2, char ch3, char ch4>
struct separator< ch0, ch1, ch2, ch3, ch4>
{
  typedef fas::metalist::tstring metatype; 
  typedef const char* value_type;
  value_type operator()() const 
  {
    const char result[]={ch0, ch1, ch2, ch3, ch4};
    return result; 
  } 
};
*/

#endif

