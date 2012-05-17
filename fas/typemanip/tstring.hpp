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


#endif

