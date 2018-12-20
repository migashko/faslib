//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2018
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_FUNCTIONAL_IGNORE_ARGS_HPP
#define FAS_FUNCTIONAL_IGNORE_ARGS_HPP

#include <fas/typemanip/empty_type.hpp>

namespace fas{

template<typename T>
inline void ignore_arg(const T&){}

template<typename T1>
inline void ignore_args(const T1& =T1() ){}

template<typename T1, typename T2>
inline void ignore_args(const T1& =T1(), const T2& =T2() ){}

template<typename T1, typename T2, typename T3>
inline void ignore_args(const T1& =T1(), const T2& =T2(), const T3& =T3() ){}

template<typename T1, typename T2, typename T3, typename T4>
inline void ignore_args(const T1& =T1(), const T2& =T2(), const T3& =T3(), const T4& =T4() ){}

template<typename T1, typename T2, typename T3, typename T4, typename T5>
inline void ignore_args(const T1& =T1(), const T2& =T2(), const T3& =T3(), const T4& =T4(), const T5& =T5() ){}

}

#endif
