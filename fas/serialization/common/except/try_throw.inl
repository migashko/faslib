//
// Author: Vladimir Migashko <migashko@gmail.com>, (C) 2012
//
// Copyright: See COPYING file that comes with this distribution
//

/*
 * Usage:
 * #include <utility>
 * #include <you_path_to_tags/tags.hpp>
 * namespace you_space
 * {
 * #include <fas/serialization/common/except/try_throw.hpp>
 * }
*/

template<typename T, typename E>
inline void throw_( T& t, const E& e)
{
  return t.get_aspect().template get<_except_>()( t, e);
}

template<typename T, typename E, typename R>
inline R throw_( T& t, const E& e, R r)
{
  return t.get_aspect().template get<_except_>()( t, e, r);
}

template<typename T, typename E, typename R, typename RR>
inline std::pair<R, RR> throw_( T& t, const E& e, R r, RR rr) 
{
  return std::pair<R, RR>( t.get_aspect().template get<_except_>()( t, e, r), rr);
}

template<typename T>
inline bool try_( T& t)
{
  return ! t.get_aspect().template get<_except_>();
}
