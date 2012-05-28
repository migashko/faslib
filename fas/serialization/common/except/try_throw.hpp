//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

#ifndef FAS_SERIALIZATION_COMMON_EXCEPT_TRY_THROW_HPP
#define FAS_SERIALIZATION_COMMON_EXCEPT_TRY_THROW_HPP

#include <utility>

namespace fas{ namespace serialization{

template<typename Tg, typename T, typename E>
inline void throw_t( T& t, const E& e)
{
  typedef Tg _except_;
  return t.get_aspect().template get<_except_>()( t, e);
}

template<typename Tg, typename T, typename E, typename R>
inline R throw_t( T& t, const E& e, R r)
{
  typedef Tg _except_;
  return t.get_aspect().template get<_except_>()( t, e, r);
}

template<typename Tg, typename T, typename E, typename R, typename RR>
inline std::pair<R, RR> throw_t( T& t, const E& e, R r, RR rr) 
{
  typedef Tg _except_;
  return std::pair<R, RR>( t.get_aspect().template get<_except_>()( t, e, r), rr);
}

template<typename Tg, typename T>
inline bool try_t( T& t)
{
  typedef Tg _except_;
  return ! t.get_aspect().template get<_except_>();
}

}}

#endif
