#ifndef FAS_SERIALIZATION_JSON_EXCEPT_JSON_THROW_HPP
#define FAS_SERIALIZATION_JSON_EXCEPT_JSON_THROW_HPP

#include <fas/serialization/json/except/tags.hpp>
#include <utility>

namespace fas{ namespace json{ 

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

// #define try_( t ) !t.get_aspect().template get<_except_>()


template<typename T>
inline bool try_( T& t)
{
  return ! t.get_aspect().template get<_except_>();
}




}}

#endif
